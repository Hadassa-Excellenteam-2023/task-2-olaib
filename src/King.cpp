#include "King.h"
#include "FactoryPieces.h"


bool King::m_registerit = FactoryPieces::registerit(KING_CHAR, [](const char& _ch, const Location& loc, PlayerColor color, Board* board)
	-> unique_ptr<Piece> {return std::make_unique<King>(_ch, loc, color  ,board); }
);

King::King(const char& _ch, const Location& loc, PlayerColor color, Board* board) : Piece(_ch, loc, color, board) {}

bool King::isLegalMovement(const Location& source, const Location& dest) const
{
	int rowDiff = abs(source.getLetter() - dest.getLetter()),
		colDiff = abs(source.getNum() - dest.getNum());

	if (colDiff != 0 && colDiff != 1)
		return false;
	
	if (rowDiff > 1 || (rowDiff == 0 && colDiff == 0))
		return false;

	return true;
}
