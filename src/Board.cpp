#include "Board.h"
#include "King.h"
#include "Rook.h"
#include "Pawn.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "EmptySlot.h"
#include <algorithm>
#include  <iterator>
#include "unordered_map"
#include <exception>
#include <stdexcept>

namespace {
	Type char2Type(const char& _ch) {
		switch (std::tolower(_ch)) {
		case 'k':
			return Type::King;
		case 'q':
			return Type::Queen;
		case 'r':
			return Type::Rook;
		case 'b':
			return Type::Bishop;
		case 'n':
			return Type::Knight;
		case 'p':
			return Type::Pawn;
		case '#':
			return Type::EmptySlot;
		default:
			return Type::Unknown;
		}
	}
	std::unique_ptr<Piece> char2Piece(const char& _ch)
	{
		switch (char2Type(_ch))
		{
		case Type::King:
			return std::make_unique<King>(_ch);
		case Type::Queen:
			return std::make_unique<Queen>(_ch);
		case Type::Rook:
			return std::make_unique<Rook>(_ch);
		case Type::Bishop:
			return std::make_unique<Bishop>(_ch);
		case Type::Knight:
			return std::make_unique<Knight>(_ch);
		case Type::Pawn:
			return std::make_unique<Pawn>(_ch);
		case Type::EmptySlot:
			return std::make_unique<EmptySlot>(_ch);
			//unknown
		default:
			throw std::invalid_argument("Invalid character");
		}
	}
}
Board::Board(const string& start)
{
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		for (size_t j = 0; j < BOARD_SIZE; j++)
		{
			m_board[i][j] = char2Piece(std::tolower(start[i * BOARD_SIZE + j]));
		}
	}
}

string Board::getBoard() const
{
	string boardString;;
	boardString.reserve(BOARD_SIZE * BOARD_SIZE); // reserve space for performance

	for (const auto& row : m_board)
		for (const auto& col : row)
			boardString += col->getChar();

	return boardString;
}

