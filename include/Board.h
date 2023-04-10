#pragma once
#include "Piece.h"
#include <array>
#include "memory"

using std::array;
using std::unique_ptr;
const auto START_BOARD = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
const auto BOARD_SIZE = 8;

enum CodeRes : int {
	EmptyPiece = 11,
	YourPieceFoundAtDest = 13,
	IlligalMove = 12,
	CheckMateOnMyself = 31,
	CheckMateOnMOpponent = 41,
	LegalMove = 42,
};

class Board {
public:
	Board(const string& start = START_BOARD);
	int getCodeResponse(const string& inpt, PlayerColor playerTurn);
	auto getBoard() { return m_initBoard; }
	Location getOpponentKingLoc(PlayerColor myColor) const;
	void movePiece(const Location& source, const Location& dest);
	bool isPathOk(const char& letter, int n) const;
private:
	// =========================== PRIVATE FUNCTIONS =================
	bool isKingInCheck(const Location& source, const Location& dest) const;
	// ============================= MEMBERS =========================
	array <array< unique_ptr<Piece>, BOARD_SIZE> ,BOARD_SIZE> m_board;
	string m_initBoard;
};