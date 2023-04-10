#pragma once
#include "Piece.h"
#include "FactoryPieces.h"
const auto QUEEN_CHAR = 'Q';

class Queen : public Piece {
public:
	Queen(const char& _ch, const Location& loc, PlayerColor color);
	bool isLegalMovement(const Location& source, const Location& dest)const override;
private:
	static bool m_registerit;
};