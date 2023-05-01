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
    int diffL = source.getLetter() - dest.getLetter();
    int diffN = source.getNum() - dest.getNum();

    if (abs(diffL) != abs(diffN))
        return false;

    int signL = (diffL > 0) ? -1 : 1;
    int signN = (diffN > 0) ? -1 : 1;

    for (char l = source.getLetter() + signL, n = source.getNum() + signN;
        l != dest.getLetter(); l += signL, n += signN)
    {
        if (!m_board->isEmptySlot(Location(l, n)))
            return false;
    }

    return true;

}




