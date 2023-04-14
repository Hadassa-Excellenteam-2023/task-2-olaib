#pragma once
#include "Piece.h"
#include <array>
#include "memory"
using std::array;
using std::unique_ptr;

const auto START_BOARD = string("RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr");
const auto BOARD_SIZE = 8;
// ============================== CODE RESPONCE ENUM ==================
enum CodeRes : int {
	EmptyPiece = 11,
	NoteYourPiece = 12,
	YourPieceFoundAtDest = 13,
	IlligalMove = 21,
	CheckMateOnMyself = 31,
	CheckMateOnMOpponent = 41,
	LegalMove = 42,
};

//=====================================================================
class Board {
public:
	// =========================== C-TOR ==============================
	Board(const std::string& start = START_BOARD);

	// =========================== METHODS ============================

	int getCodeResponse(const string& inpt, PlayerColor playerTurn);
	const string& getStringBoard() const{ return m_stringBoard;}
	Location getOpponentKingLoc(PlayerColor myColor) const;
	void move(const Location& source, const Location& dest);
	bool isEmptySlot(const Location& loc) const;
private:
	// =========================== PRIVATE FUNCTIONS =================
	void init(const string& start);
	bool isKingInCheck(const Location& source, const Location& dest) const;
	// ============================= MEMBERS =========================
	array <array< unique_ptr<Piece>, BOARD_SIZE+1> ,BOARD_SIZE> m_board;
	string m_stringBoard;
};