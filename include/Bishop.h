#pragma once
#include "Piece.h"
#include "FactoryPieces.h"
const auto BISHOP_CHAR = 'P';

class Bishop : public Piece {
public:
	Bishop(const char& _ch, const Location& loc, PlayerColor color);
	bool isLegalMovement(const Location& source, const Location& dest)const override;
private:
	static bool m_registerit;
};