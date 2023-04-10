#include "Pawn.h"


bool Pawn::m_registerit = FactoryPieces::registerit(PAWN_CHAR, [](const char& _ch, const Location& loc, PlayerColor color)
	-> unique_ptr<Piece> {return std::make_unique<Pawn>(_ch, loc, color); }
);

Pawn::Pawn(const char& _ch, const Location& loc, PlayerColor color) : Piece(_ch, loc, color) {}