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
    if (source.l == dest.l && source.n != dest.n) 
    {
        int step = (dest.n - source.n > 0) ? 1 : -1;
        for (int n = (source.n + step); n != dest.n; n += step) {
            if (!m_board->isEmptySlot(Location(source.l, n))) {
                return false;
            }
        }
        return true;
    }
    else if (source.l != dest.l && source.n == dest.n) 
    {
        int step = (dest.l - source.l > 0) ? 1 : -1;
        for (char l = (source.l + step); l != dest.l; l += step) {
            if (!m_board->isEmptySlot(Location(l, source.n))) {
                return false;
            }
        }
        return true;
    }
    //else
    return false;
}
