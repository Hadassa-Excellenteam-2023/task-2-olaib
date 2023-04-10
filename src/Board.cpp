#include "Board.h"
#include "King.h"
#include "Rook.h"
#include "Pawn.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "EmptySlot.h"
#include <algorithm>
#include  <iterator>
#include "unordered_map"
#include <exception>
#include <stdexcept>
#include <iostream>

const auto A_CHAR = 'A';
const auto WHITE_KING = 'K';// capital litter
const auto BLACK_KING = 'k';// small litter

namespace{
	auto getLoc(size_t row, size_t col) {
		return Location(toChar(row), col + 1);
	}
	auto toChar(const size_t& row) {
		char letter = static_cast<char>(A_CHAR + row);
		return letter;
	}


	auto getPlayerColor(char _ch) { return std::islower(_ch) ? PlayerColor::Black : PlayerColor::White; }
	
	auto charRow2Int(const char& row) {
		return static_cast<int>(row - A_CHAR);
	}

	auto toInt(const char& _ch)
	{
		return static_cast<int>(_ch);
	}
}



Board::Board(const string& start) : m_initBoard(start)
{
	auto strIndx = 0;
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		for (size_t j = 0; j < BOARD_SIZE; j++)
		{
			const auto _ch = start[strIndx++];
			m_board[i][j] = FactoryPieces::create(std::toupper(_ch), getLoc(i, j),getPlayerColor(_ch));
		}
	}
}




int Board::getCodeResponse(const string& inpt, PlayerColor playerTurn)
{
	Location source(inpt[0], toInt(inpt[1])),
			 dest(inpt[2], toInt(inpt[3]));

	auto& sourcePiece = m_board[charRow2Int(source.l)][source.n - 1];

	
	if (dynamic_cast<EmptySlot*>(sourcePiece.get())) {
		return CodeRes::EmptyPiece; // return code: 11
	}

	auto& destPiece = m_board[charRow2Int(dest.l)][source.n - 1];

	if (sourcePiece->getPlyrColor() != playerTurn ||
		sourcePiece->getPlyrColor() == destPiece->getPlyrColor() ||
		!sourcePiece->isLegalMovement(source, dest))
		return CodeRes::IlligalMove; // return code: 12

	// check if the movement cause check on my king piece
	std::swap(source, dest);
	m_board[charRow2Int(dest.l)][dest.n]->setLocation(dest);

	if (isKingInCheck(source, dest))
		return CodeRes::CheckMateOnMyself;// return code: 31

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

void Board::movePiece(const Location& source, const Location& dest)
{
	auto& sourcePiece = m_board[charRow2Int(source.l)][source.n - 1];

	auto& destPiece = m_board[charRow2Int(dest.l)][dest.n - 1];
	// swap places
	std::swap(sourcePiece, destPiece);
	destPiece->setLocation(source);
	sourcePiece->setLocation(dest);

}

bool Board::isPathOk(const char& letter, int n) const
{
	//todo: check if emptyslot????
	 return !m_board[charRow2Int(letter)][n].get();
}

bool Board::isKingInCheck(const Location& source, const Location& dest) const
{
	auto& sourcePiece = m_board[charRow2Int(source.l)][source.n - 1];

	auto& destPiece = m_board[charRow2Int(dest.l)][dest.n - 1];

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











