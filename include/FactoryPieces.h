#pragma once
#include <memory> 
#include <map>
#include "Piece.h"
using std::unique_ptr;

class FactoryPieces
{
public:
	using pFunc = unique_ptr<Piece>(*)(const char&, const Location&, PlayerColor color);
	static unique_ptr<Piece> create(const char&, const Location&, PlayerColor color);
	static bool registerit(const char, pFunc);
private:
	static auto& getPiecesMap() {
		static std::map<const char, pFunc> map;
		return map;
	}
};