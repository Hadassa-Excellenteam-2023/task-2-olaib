#include "Queen.h"


bool Queen::m_registerit = FactoryPieces::registerit(QUEEN_CHAR, [](const char& _ch, const Location& loc, PlayerColor color)
	-> unique_ptr<Piece> {return std::make_unique<Queen>(_ch, loc, color); }
);

Queen::Queen(const char& _ch, const Location& loc, PlayerColor color) : Piece(_ch, loc, color) {}