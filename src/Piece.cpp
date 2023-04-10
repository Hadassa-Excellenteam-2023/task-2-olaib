#include "Piece.h"

Piece::Piece(const string& myChar, Location loc) :m_char(myChar), m_loc(loc) {}

void Piece::setLocation(Location dist)
{
	m_loc = dist;
}
