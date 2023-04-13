#pragma once
#include <string>
#include "Location.h"
#include "PlayerColor.h"
#include <memory>

using std::string;
using std::unique_ptr;

class Board;


class Piece {
public:
	Piece(const char& myChar,const Location& loc, PlayerColor color, Board* board);
	virtual char getChar() const { return m_char; }
	virtual void setLocation(Location dist);
	virtual Location getLocation() const;
	virtual PlayerColor getPlyrColor() const;
	virtual bool isLegalMovement(const Location& source, const Location& dest) const = 0;
	virtual bool checkOpponent(const Location& source);
	virtual bool checkOpponent(const Location& source, const Location& dest);
	virtual ~Piece() = default;
private:
	char m_char;
	Location m_loc;
	PlayerColor m_color;
protected:
	Board* m_board;
};