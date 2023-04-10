#include "Piece.h"


Piece::Piece(const char& myChar, const Location& loc, PlayerColor color) : m_char(myChar), m_loc(loc)
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

