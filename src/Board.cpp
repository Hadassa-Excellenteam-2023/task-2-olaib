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


const char WHITE_KING = 'K', // capital litter
		   BLACK_KING = 'k', // small litter
           EMPTY_SLOT = '#'; // small litter
const int MAX_USER_INPT_LEN = 4,
		  A_ASCII = 97,
		  H_ASCII = 104;
// ===================================================
namespace {
	// int row to char
	auto toChar(const int& row) {
		if (row < 1 || row > BOARD_SIZE)
			throw(std::invalid_argument("Invalid Row: " + row));
		return (char)(row + A_ASCII);
	}

	auto getLoc(int row, int col) {
		return Location(toChar(row), col);
	}

	auto getPlayerColor(char _ch) { return std::islower(_ch) ? PlayerColor::Black : PlayerColor::White; }

	auto charRow2Int(const char& row) {
		if (row < A_ASCII || row > H_ASCII)
			throw(std::invalid_argument("Invalid Row: " + row));
		return (int)row - A_ASCII;
	}
	// char to int
	auto toInt(const char& _ch)
	{
		if (_ch < '0' || _ch > '7')
			throw(std::invalid_argument("Invalid Column: " + _ch));
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

int Board::getCodeResponse(const string& inpt, PlayerColor playerTurn) {
	Location source(inpt[0], toInt(inpt[1]));
	Location dest(inpt[2], toInt(inpt[3]));

	const auto sourceL = charRow2Int(source.getLetter());
	auto sourcePiece = m_board[sourceL][source.getNum()].get();
	if (!sourcePiece) {
		return CodeRes::EmptyPiece;
	}

	if (sourcePiece->getPlyrColor() != playerTurn) {
		return CodeRes::NoteYourPiece;
	}

	int destL = charRow2Int(dest.getLetter());
	auto destPiece = m_board[destL][dest.getNum()].get();

	if (destPiece && (sourcePiece->getPlyrColor() == destPiece->getPlyrColor())) {
		return CodeRes::YourPieceFoundAtDest;
	}

	if (!sourcePiece->isLegalMovement(source, dest)) {
		return CodeRes::IlligalMove;
	}

	std::swap(sourcePiece, destPiece);
	destPiece->setLocation(dest);
	if (sourcePiece) {
		if (isKingInCheck(source, dest)) {
			destPiece->setLocation(source);
			std::swap(sourcePiece, destPiece);
			return CodeRes::CheckMateOnMyself;
		}
	}

	destPiece->setLocation(source);
	std::swap(sourcePiece, destPiece);

	if (sourcePiece->checkOpponent(source, dest)) {
		move(source, dest);
		return CodeRes::CheckMateOnMOpponent;
	}

	move(source, dest);
	return CodeRes::LegalMove;
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
	auto& sourcePiece = m_board[charRow2Int(source.getLetter())][source.getNum()];

	auto& destPiece = m_board[charRow2Int(dest.getLetter())][dest.getNum()];
	// swap places
	std::swap(sourcePiece, destPiece);
	destPiece->setLocation(dest);
	sourcePiece.release();
}

bool Board::isEmptySlot(const Location& loc) const
{
	//check if emptyslot - no piece found at wanted location
	return m_board[charRow2Int(loc.getLetter())][loc.getNum()] == nullptr;
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
				FactoryPieces::create(std::toupper(_ch), getLoc(row + 1, col), getPlayerColor(_ch), this);
		}
	}
}

bool Board::isKingInCheck(const Location& source, const Location& dest) const
{
	auto sourcePiece = m_board[charRow2Int(source.getLetter())][source.getNum()].get();

	auto destPiece = m_board[charRow2Int(dest.getLetter())][dest.getNum()].get();

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
