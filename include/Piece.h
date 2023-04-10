#pragma once
#include <string>
#include "Location.h"
#include "PlayerColor.h"

using std::string;

class Piece {
public:
	Piece(const char& myChar,const Location& loc, PlayerColor color);
	virtual char getChar() const { return m_char; }
	virtual void setLocation(Location dist);
	virtual Location getLocation() const;
	virtual PlayerColor getPlyrColor() const;
	virtual bool isLegalMovement(const Location& source, const Location& dest) const = 0;
	virtual bool checkOpponent(const Location& loc) = 0;
private:
	char m_char;
	Location m_loc;
	PlayerColor m_color;
};