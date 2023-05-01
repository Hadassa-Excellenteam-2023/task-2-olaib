#pragma once
#include "Piece.h"
const auto PAWN_CHAR = 'P';

class Pawn : public Piece {
public:
	Pawn(const char& _ch, const Location& loc, PlayerColor color, Board* board);
	bool isLegalMovement(const Location& source, const Location& dest)const override;
private:
	static bool m_registerit;
};