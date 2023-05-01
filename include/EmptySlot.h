#pragma once
#include "Piece.h"
#include "FactoryPieces.h"
const auto EMPTY_SLOT_CHAR = '#';


class EmptySlot : public Piece {
public:
	EmptySlot(const char& _ch, const Location& loc, PlayerColor color);
private:
	static bool m_registerit;
};