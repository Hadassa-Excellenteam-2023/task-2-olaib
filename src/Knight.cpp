#include "Knight.h"
#include "FactoryPieces.h"

bool Knight::m_registerit = FactoryPieces::registerit(KNIGHT_CHAR, [](const char& _ch, const Location& loc, PlayerColor color, Board* board)
	-> unique_ptr<Piece> {return std::make_unique<Knight>(_ch, loc, color, board); }
);

Knight::Knight(const char& _ch, const Location& loc, PlayerColor color, Board* board) : Piece(_ch, loc, color, board) {}

bool Knight::isLegalMovement(const Location& source, const Location& dest) const
{
	int diffL = abs(source.l - dest.l),
		diffN = abs(source.n - dest.n);

	return (((diffL == 1) && (diffN == 2)) || ((diffL == 2) && (diffN == 1)));
}
