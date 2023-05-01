#pragma once
#include "Rook.h"
#include "Bishop.h"
const auto QUEEN_CHAR = 'Q';

class Queen : public Bishop ,public Rook {
public:
	Queen(const char& _ch, const Location& loc, PlayerColor color, Board* board);
	bool isLegalMovement(const Location& source, const Location& dest)const override;
private:
	static bool m_registerit;
};