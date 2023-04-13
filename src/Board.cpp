#include "Board.h"
#include "King.h"
#include "Rook.h"
#include "Pawn.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "FactoryPieces.h"
#include <algorithm>
#include  <iterator>
#include <exception>
#include <stdexcept>


const char WHITE_KING   = 'K', // capital litter
		   BLACK_KING   = 'k', // small litter
		   EMPTY_SLOT   = '#'; // small litter
const auto MAX_USER_INPT_LEN = 4;

const auto INVALID_LOC = "Invalid Location : ";


// ===================================================
namespace{
	// int row to char
	auto toChar(const int& row) {
		switch (row)
		{
		case 0: return 'a';
		case 1: return 'b';
		case 2: return 'c';
		case 3: return 'd';
		case 4: return 'e';
		case 5: return 'f';
		case 6: return 'g';
		case 7: return 'h';
		default:
			throw(std::invalid_argument("Invalid Row: " + row));
		}
	}

	auto getLoc(int row, int col) {
		return Location(toChar(row), col);
	}

	auto getPlayerColor(char _ch) { return std::islower(_ch) ? PlayerColor::Black : PlayerColor::White; }
	
	auto charRow2Int(const char& row) {
		switch (row)
		{
		case 'a': return 0;
		case 'b': return 1;
		case 'c': return 2;
		case 'd': return 3;
		case 'e': return 4;
		case 'f': return 5;
		case 'g': return 6;
		case 'h': return 7;
		default:
			throw(std::invalid_argument("Invalid Row: " + row));
		}
	}
	// char to int
	auto toInt(const char& _ch)
	{
		return (int)_ch - 48;
	}
}
Board::Board(const string& start) : m_stringBoard(start)
{
	try{
		init(start);
	}
	catch (std::invalid_argument e) { throw; }
	catch (std::bad_alloc e) { throw; }
	catch (std::out_of_range e) { throw; }
	catch (...)
	{
		throw;
	}
}

int Board::getCodeResponse(const string& inpt, PlayerColor playerTurn)
{
	Location source(inpt[0], toInt(inpt[1])),
			 dest(inpt[2], toInt(inpt[3]));

	const auto sourceL = charRow2Int(source.l);
	// the current piece
	auto sourcePiece = m_board[sourceL][source.n].get();
	if (!sourcePiece) {
		return CodeRes::EmptyPiece; // return code: 11
	}

	if (sourcePiece->getPlyrColor() != playerTurn)
		return CodeRes::NoteYourPiece; // return code 12

	int destL = charRow2Int(dest.l);

	auto destPiece = m_board[destL][dest.n].get();

	if (destPiece && (sourcePiece->getPlyrColor() == destPiece->getPlyrColor()))
		return CodeRes::YourPieceFoundAtDest; // return code 13

	if (!sourcePiece->isLegalMovement(source, dest))
		return CodeRes::IlligalMove; //return code 21

	// temporary movement to check if was check on king
		std::swap(sourcePiece, destPiece);
		destPiece->setLocation(dest);
	if (sourcePiece) {

		if (isKingInCheck(source, dest))
		{
			destPiece->setLocation(source);
			std::swap(sourcePiece, destPiece);
			return CodeRes::CheckMateOnMyself; // return code 31
		}
	}

	destPiece->setLocation(source);
	std::swap(sourcePiece, destPiece);

	if (sourcePiece->checkOpponent(source, dest))
	{
		move(source, dest);
		return CodeRes::CheckMateOnMOpponent; // return code 41
	}

	move(source, dest);
	return CodeRes::LegalMove; // return code 42
}

Location Board::getOpponentKingLoc(PlayerColor myColor)const
{
	for (auto& row : m_board)
		for (auto& piece : row)
		{
			if (piece && (myColor != piece->getPlyrColor() &&
				(piece->getPlyrColor() == WHITE_KING || piece->getPlyrColor() == BLACK_KING)))
				return piece->getLocation();
		}
}

void Board::move(const Location& source, const Location& dest)
{
	auto& sourcePiece = m_board[charRow2Int(source.l)][source.n];

	auto& destPiece = m_board[charRow2Int(dest.l)][dest.n];
	// swap places
	std::swap(sourcePiece, destPiece);
	destPiece->setLocation(dest);
	sourcePiece.release();
}

bool Board::isEmptySlot(const Location& loc) const
{
	//check if emptyslot - no piece found at wanted location
	return m_board[charRow2Int(loc.l)][loc.n] == nullptr;
}

void Board::init(const string& start)
{
	auto starIndx = 0;
	for (size_t row = 0; row < BOARD_SIZE; row++)
	{
		for (size_t col = 1; col <= BOARD_SIZE; col++)
		{
			const auto _ch = start[starIndx++];

			m_board[row][col] = (_ch == EMPTY_SLOT) ? nullptr :
				FactoryPieces::create(std::toupper(_ch), getLoc(row, col), getPlayerColor(_ch), this);
		}
	}
}

bool Board::isKingInCheck(const Location& source, const Location& dest) const
{
	auto sourcePiece = m_board[charRow2Int(source.l)][source.n].get();

	auto destPiece = m_board[charRow2Int(dest.l)][dest.n].get();

	auto destKing = destPiece->getChar();

	if (sourcePiece && destKing == WHITE_KING || destKing == BLACK_KING)
		return false;

	for (auto& row : m_board)
		for (auto& piece : row)
		{
			if (piece && piece->getPlyrColor() != destPiece->getPlyrColor()
				&& piece->checkOpponent(piece->getLocation()))
			{
				return true;
			}
		}
	// king not in check
	return false;
}
