#pragma once
#include <string>
#include "Location.h"
using std::string;

class Piece {
public:
	Piece(const string& myChar, Location loc);
	virtual string getChar() const { return m_char; }
	virtual void setLocation(Location dist);

private:
	string m_char;
	Location m_loc;
};