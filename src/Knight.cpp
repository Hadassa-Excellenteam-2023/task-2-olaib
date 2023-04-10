#include "Knight.h"

bool Knight::m_registerit = FactoryPieces::registerit(KNIGHT_CHAR, [](const char& _ch, const Location& loc, PlayerColor color)
	-> unique_ptr<Piece> {return std::make_unique<Knight>(_ch, loc, color); }
);

Knight::Knight(const char& _ch, const Location& loc, PlayerColor color) : Piece(_ch, loc, color) {}
