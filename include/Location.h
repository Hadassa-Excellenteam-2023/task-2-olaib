#pragma once

typedef struct Location
{
    char l;
    int n;

    Location(const char& letter, const int& num) : l(letter), n(num) {}
    Location operator() (const char& letter, const int& num) const { return Location(letter, num); }

} Location;

const bool operator==(const Location& lhs, const Location& rhs)
{
    return lhs.l == rhs.l && lhs.n == rhs.n;
}

const bool operator!=(const Location& lhs, const Location& rhs)
{
    return !(lhs == rhs);
}