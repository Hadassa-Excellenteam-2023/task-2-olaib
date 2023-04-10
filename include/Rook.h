#pragma once
#include "Piece.h"
#include "FactoryPieces.h"
const auto ROOK_CHAR = 'R';

class Rook : public Piece {
public:
	Rook(const char& _ch, const Location& loc, PlayerColor color);
	bool isLegalMovement(const Location& source, const Location& dest)const override;
private:
	static bool m_registerit;
};