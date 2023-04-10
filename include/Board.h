#pragma once
#include "Piece.h"
#include <array>
#include "memory"

using std::array;
using std::unique_ptr;
const auto START_BOARD = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
const auto BOARD_SIZE = 8;

enum class Type { King, Queen, Rook, Bishop, Knight, Pawn, EmptySlot, Unknown };

class Board {
public:
	Board(const string& start = START_BOARD);
	string getBoard() const;

private:
	array <array< unique_ptr<Piece>, BOARD_SIZE> ,BOARD_SIZE> m_board;
};