#include "Bishop.h"
#include "FactoryPieces.h"
#include "Board.h"

bool Bishop::m_registerit = FactoryPieces::registerit(BISHOP_CHAR, [](const char& _ch, const Location& loc, PlayerColor color, Board* board)
	-> unique_ptr<Piece> {return std::make_unique<Bishop>(_ch, loc, color, board); }
);

Bishop::Bishop(const char& _ch, const Location& loc, PlayerColor color, Board* board) : Piece(_ch, loc, color, board) {}

bool Bishop::isLegalMovement(const Location& source, const Location& dest) const
{
	return isBishopLegalMove(source, dest);
}

bool Bishop::isBishopLegalMove(const Location& source, const Location& dest) const
{
	int diffL = abs(source.l - dest.l),
		diffN = abs(source.n - dest.n);

	if (diffL != diffN)
		return false;

	auto dir = Location((source.l < dest.l) ? 1 : -1, (source.n < dest.n) ? 1 : -1);

	auto loc = Location(source.l + dir.l, source.n + dir.n);

	while (loc != dest)
	{
		if (!m_board->isEmptySlot(loc))
			return false;
		loc.l += dir.l;
		loc.n += dir.n;
	}
	return true;
}




