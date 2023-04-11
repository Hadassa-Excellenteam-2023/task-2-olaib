#pragma once
#include "Piece.h"
const auto BISHOP_CHAR = 'P';

class Bishop : virtual public Piece {
public:
	Bishop(const char& _ch, const Location& loc, PlayerColor color, Board* board);
	bool isLegalMovement(const Location& source, const Location& dest)const override;
protected:
	bool isBishopLegalMove(const Location& source, const Location& dest) const;
private:
	static bool m_registerit;
};