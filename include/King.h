#pragma once
#include "Piece.h"
#include "FactoryPieces.h"
const auto KING_CHAR = 'K';



class King : public Piece {
public:
	King(const char& _ch, const Location& loc, PlayerColor color);
	bool isLegalMovement(const Location& source, const Location& dest)const override;
private:
	static bool m_registerit;
};