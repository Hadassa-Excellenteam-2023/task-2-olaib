#include "Pawn.h"
#include "FactoryPieces.h"
const auto SECOND_ROW = 'b';
const auto SEVENTH_ROW = 'g';


bool Pawn::m_registerit = FactoryPieces::registerit(PAWN_CHAR, [](const char& _ch, const Location& loc, PlayerColor color, Board* board)
	-> unique_ptr<Piece> {return std::make_unique<Pawn>(_ch, loc, color, board); }
);

Pawn::Pawn(const char& _ch, const Location& loc, PlayerColor color, Board* board) : Piece(_ch, loc, color, board) {}

bool Pawn::isLegalMovement(const Location& source, const Location& dest) const
{
	int diffL = source.getLetter() - dest.getLetter(), destN = dest.getNum();
	auto amIBlack = getPlyrColor() == PlayerColor::Black;
	char sourceL = source.getLetter(), destL = dest.getLetter();

	if ((!amIBlack && sourceL == SECOND_ROW && source == Location(destL - 2, destN))
		|| (amIBlack && sourceL == SEVENTH_ROW && source == Location(destL + 2, destN)))

		return true;

	if ((abs(diffL) != 1 || source.getNum() != destN)
		|| ((!amIBlack && diffL >= 0) || (amIBlack && diffL <= 0)))
		return false;

	return true;

}
