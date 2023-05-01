#include "EmptySlot.h"


bool EmptySlot::m_registerit = FactoryPieces::registerit(EMPTY_SLOT_CHAR, [](const char& _ch, const Location& loc, PlayerColor color)
	-> unique_ptr<Piece> {return std::make_unique<EmptySlot>(_ch, loc, color); }
);

EmptySlot::EmptySlot(const char& _ch, const Location& loc, PlayerColor color) : Piece(_ch, loc, color) {}


