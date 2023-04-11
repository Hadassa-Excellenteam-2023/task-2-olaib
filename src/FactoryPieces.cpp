#include "FactoryPieces.h"

unique_ptr<Piece> FactoryPieces::create(const char& _ch, const Location& loc, PlayerColor color, Board* board)
{
	auto it = FactoryPieces::getPiecesMap().find(_ch);
	if (it == FactoryPieces::getPiecesMap().end())
		return nullptr;
	return it->second(_ch, loc, color, board);
}

bool FactoryPieces::registerit(const char _ch, pFunc func)
{
	FactoryPieces::getPiecesMap().emplace(_ch, func);
	return true;
}
