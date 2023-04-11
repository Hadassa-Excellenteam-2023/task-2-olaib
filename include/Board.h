#pragma once
#include "Piece.h"
#include <array>
#include "memory"
#include<iostream>
using std::array;
using std::unique_ptr;

const auto START_BOARD = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
const auto BOARD_SIZE = 8;
// ============================== CODE RESPONCE ENUM ==================
enum CodeRes : int {
	EmptyPiece = 11,
	YourPieceFoundAtDest = 13,
	IlligalMove = 12,
	CheckMateOnMyself = 31,
	CheckMateOnMOpponent = 41,
	LegalMove = 42,
};

//=====================================================================
class Board {
public:
	// =========================== C - TOR ============================
	Board(const std::string& start = START_BOARD);

	// =========================== METHODS ============================

	int getCodeResponse(const string& inpt, PlayerColor playerTurn);
	//auto getBoard() const{ return m_initBoard;}
	Location getOpponentKingLoc(PlayerColor myColor) const;
	void move(const Location& source, const Location& dest);
	bool isEmptySlot(const Location& loc) const;
private:
	
	// =========================== PRIVATE FUNCTIONS =================
	bool isKingInCheck(const Location& source, const Location& dest) const;
	// ============================= MEMBERS =========================
	array <array< unique_ptr<Piece>, BOARD_SIZE> ,BOARD_SIZE> m_board;
	//std::string m_initBoard;
};