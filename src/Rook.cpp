#include "Rook.h"


bool Rook::m_registerit = FactoryPieces::registerit(ROOK_CHAR, [](const char& _ch, const Location& loc, PlayerColor color)
	-> unique_ptr<Piece> {return std::make_unique<Rook>(_ch, loc, color); }
);

Rook::Rook(const char& _ch, const Location& loc, PlayerColor color) : Piece(_ch, loc, color) {}