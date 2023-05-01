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
    if (source.getLetter() == dest.getLetter() && source.getNum() != dest.getNum())
    {
        int step = (dest.getNum() - source.getNum() > 0) ? 1 : -1;
        for (int n = (source.getNum() + step); n != dest.getNum(); n += step) {
            if (!m_board->isEmptySlot(Location(source.getLetter(), n))) {
                return false;
            }
        }
        return true;
    }
    else if (source.getLetter() != dest.getLetter() && source.getNum() == dest.getNum())
    {
        int step = (dest.getLetter() - source.getLetter() > 0) ? 1 : -1;
        for (char l = (source.getLetter() + step); l != dest.getLetter(); l += step) {
            if (!m_board->isEmptySlot(Location(l, source.getNum()))) {
                return false;
            }
        }
        return true;
    }
    //else
    return false;
}
