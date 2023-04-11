#include "Rook.h"
#include "Board.h"
#include "FactoryPieces.h"

bool Rook::m_registerit = FactoryPieces::registerit(ROOK_CHAR, [](const char& _ch, const Location& loc, PlayerColor color, Board* board)
	-> unique_ptr<Piece> {return std::make_unique<Rook>(_ch, loc, color, board); }
);

Rook::Rook(const char& _ch, const Location& loc, PlayerColor color, Board* board) : Piece(_ch, loc, color, board) {}

bool Rook::isLegalMovement(const Location& source, const Location& dest) const
{
	return isRookLegalMove(source, dest);
}

bool Rook::isRookLegalMove(const Location& source, const Location& dest) const
{
	// Rook can only move horizontally or vertically
	if (source.l != dest.l && source.n != dest.n) {
		return false;
	}

	// Check if there is a valid path(clear) between source and destination
	int start, end, step;
	if (source.l == dest.l) {
		start = std::min(source.n, dest.n);
		end = std::max(source.n, dest.n);
		step = (source.n < dest.n) ? 1 : -1;
	}
	else {
		start = std::min(source.l, dest.l);
		end = std::max(source.l, dest.l);
		step = (source.l < dest.l) ? 1 : -1;
	}

	for (int i = start + 1; i < end; i++)
	{
		auto pathLoc = Location((source.l == dest.l) ? source.l : static_cast<char>(i),
			(source.n == dest.n) ? source.n : static_cast<int>(i));

		if (!m_board->isEmptySlot(pathLoc))
			return false;
	}
	return true;
}
