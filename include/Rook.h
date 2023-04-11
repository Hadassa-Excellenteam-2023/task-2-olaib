#pragma once
#include "Piece.h"
const auto ROOK_CHAR = 'R';

class Rook : virtual public Piece {
public:
	Rook(const char& _ch, const Location& loc, PlayerColor color, Board* board);
	bool isLegalMovement(const Location& source, const Location& dest)const override;
protected:
	bool isRookLegalMove(const Location& source, const Location& dest) const;
private:
	static bool m_registerit;
};