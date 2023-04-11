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

const int MAX_ROW = 7, MIN_ROW = 0,
MIN_COL = 0, MAX_COL = 7;
const char MAX_ROW_CHAR = 'h', MIN_ROW_CHAR = 'a',
		   WHITE_KING   = 'K', // capital litter
		   BLACK_KING   = 'k', // small litter
		   EMPTY_SLOT   = '#'; // small litter

const auto INVALID_LOC = "Invalid Location : ";


// ===================================================
namespace{
	// int row to char
	auto toChar(int row) {
		if (MIN_ROW > row || row > MAX_ROW)
			throw(std::out_of_range(INVALID_LOC + row));
		return static_cast<char>(MIN_ROW_CHAR + row);
	}

	auto getLoc(int row, int col) {
		if (MIN_COL <= col || col <= MAX_COL)
			return Location(toChar(row), col);
		//else
		throw(std::out_of_range(INVALID_LOC + std::to_string(row) + " " + std::to_string(col)));
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

Board::Board(const string& start)
{
	auto starIndx = 0;
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		for (size_t j = 0; j < BOARD_SIZE; j++)
		{
			const auto _ch = start[starIndx++];

			m_board[i][j] = (_ch == EMPTY_SLOT) ? nullptr:
				FactoryPieces::create(std::toupper(_ch), getLoc(i, j),getPlayerColor(_ch), this);
		}
	}
}

int Board::getCodeResponse(const string& inpt, PlayerColor playerTurn)
{
	Location source(inpt[0], toInt(inpt[1])),
			 dest(inpt[2], toInt(inpt[3]));
	int sourceL = charRow2Int(source.l);

	if (!m_board[sourceL][source.n]) {
		return CodeRes::EmptyPiece; // return code: 11
	}

	// the current piece
	auto sourcePiece = m_board[sourceL][source.n].get();
	std::cout << "2" << std::endl;


	if (sourcePiece->getPlyrColor() != playerTurn)
		return CodeRes::IlligalMove; // return code 12

	std::cout << "3" <<dest.l<< std::endl;
	int destL = charRow2Int(dest.l);
	std::cout << destL <<", " << dest.n << std::endl;
	std::cout << "4" << dest.l << std::endl;


	auto destPiece = m_board[destL][dest.n].get();


	if (!destPiece && sourcePiece->getPlyrColor() == destPiece->getPlyrColor())
		return CodeRes::YourPieceFoundAtDest; // return code 31

	if (!sourcePiece->isLegalMovement(source, dest))
		return CodeRes::IlligalMove; //return code 21

	std::swap(sourcePiece, destPiece);
	destPiece->setLocation(dest);

	if (isKingInCheck(source, dest))
	{
		destPiece->setLocation(source);
		std::swap(sourcePiece, destPiece);
		return CodeRes::CheckMateOnMyself; // return code 31
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
			auto pieceColor = piece->getPlyrColor();
			if (piece && (myColor != piece->getPlyrColor() &&
				(pieceColor == WHITE_KING || pieceColor == BLACK_KING)))
				return piece->getLocation();
		}
}

void Board::move(const Location& source, const Location& dest)
{
	auto& sourcePiece = m_board[charRow2Int(source.l)][source.n - 1];

	auto& destPiece = m_board[charRow2Int(dest.l)][dest.n - 1];
	// swap places
	std::swap(sourcePiece, destPiece);
	destPiece->setLocation(source);
	sourcePiece->setLocation(dest);

}

bool Board::isEmptySlot(const Location& loc) const
{
	//check if emptyslot - no piece found at wanted location
	return m_board[charRow2Int(loc.l)][loc.n].get() == nullptr;
}

bool Board::isKingInCheck(const Location& source, const Location& dest) const
{
	auto sourcePiece = m_board[charRow2Int(source.l)][source.n - 1].get();

	auto destPiece = m_board[charRow2Int(dest.l)][dest.n - 1].get();

	auto destKing = destPiece->getPlyrColor();

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
