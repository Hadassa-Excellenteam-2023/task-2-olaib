#pragma once
#include "Piece.h"
const auto KNIGHT_CHAR = 'N';

class Knight : public Piece {
public:
	Knight(const char& _ch, const Location& loc, PlayerColor color, Board* board);
	bool isLegalMovement(const Location& source, const Location& dest)const override;
private:
	static bool m_registerit;
};