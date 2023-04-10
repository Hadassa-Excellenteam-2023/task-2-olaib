#include "Bishop.h"


bool Bishop::m_registerit = FactoryPieces::registerit(BISHOP_CHAR, [](const char& _ch, const Location& loc, PlayerColor color)
	-> unique_ptr<Piece> {return std::make_unique<Bishop>(_ch, loc, color); }
);

Bishop::Bishop(const char& _ch, const Location& loc, PlayerColor color) : Piece(_ch, loc, color) {}



