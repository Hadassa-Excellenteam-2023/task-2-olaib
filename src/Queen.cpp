#include "Queen.h"
#include "FactoryPieces.h"

bool Queen::m_registerit = FactoryPieces::registerit(QUEEN_CHAR, [](const char& _ch, const Location& loc, PlayerColor color, Board* board)
	-> unique_ptr<Piece> {return std::make_unique<Queen>(_ch, loc, color, board); }
);

Queen::Queen(const char& _ch, const Location& loc, PlayerColor color, Board* board)
	: Piece::Piece(_ch, loc, color, board), Bishop(_ch, loc, color, board), Rook(_ch, loc, color, board) 
{}


bool Queen::isLegalMovement(const Location& source, const Location& dest) const
{
	return isBishopLegalMove(source, dest) || isRookLegalMove(source, dest);
}
