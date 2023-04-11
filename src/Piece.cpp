#include "Piece.h"
#include "Board.h"

Piece::Piece(const char& myChar, const Location& loc, PlayerColor color, Board* board) : m_board(board), m_char(myChar), m_loc(loc)
,m_color(color) {}


void Piece::setLocation(Location dist)
{
	m_loc = dist;
}

Location Piece::getLocation() const
{
	return m_loc;
}

PlayerColor Piece::getPlyrColor() const
{
	return m_color;
}

bool Piece::isLegalMovement(const Location&, const Location&) const
{
	return true;
}

bool Piece::checkOpponent(const Location& source)
{
	auto enemyKingLoc = Location(m_board->getOpponentKingLoc(m_color));
	return isLegalMovement(source, enemyKingLoc);

}

bool Piece::checkOpponent(const Location& source, const Location& dest)
{
	return checkOpponent(source) && isLegalMovement(dest, source);
}

