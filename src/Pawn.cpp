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
	int diffL = source.l - dest.l;
	auto amIBlack = getPlyrColor();

	if ((!amIBlack && source.l == SECOND_ROW && source == Location(dest.l - 2, dest.n))
		|| (amIBlack && source.l == SEVENTH_ROW && source == Location(dest.l + 2, dest.n)))

		return true;

	if ((abs(diffL) != 1 || source.n != dest.n)
		|| ((!amIBlack && diffL >= 0) || (amIBlack && diffL <= 0)))

		return false;

	return true;

}
