#include "Location.h"

Location Location::operator()(const char& letter, const int& num) const
{
	return Location(letter, num);
}

Location Location::operator()(char letter, int num) const
{
	return Location(letter, num);
}

const bool operator==(const Location& lhs, const Location& rhs)
{
	return lhs.l == rhs.l && lhs.n == rhs.n;
}

const bool operator!=(const Location& lhs, const Location& rhs)
{
	return !(lhs == rhs);
}
