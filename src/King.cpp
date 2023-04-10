#include "King.h"

bool King::m_registerit = FactoryPieces::registerit(KING_CHAR, [](const char& _ch, const Location& loc, PlayerColor color)
	-> unique_ptr<Piece> {return std::make_unique<King>(_ch, loc, color); }
);

King::King(const char& _ch, const Location& loc, PlayerColor color) : Piece(_ch, loc, color) {}

bool King::isLegalMovement(const Location& source, const Location& dest) const
{
	
}

