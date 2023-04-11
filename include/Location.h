#pragma once

typedef struct Location
{
    char l;
    int n;
    Location(const char& letter = 'a', const int& num = 0) : l(letter), n(num) {}
    Location operator() (const char& letter, const int& num) const;
    Location operator() (char letter, int num) const;
} Location;

const bool operator==(const Location& lhs, const Location& rhs);

const bool operator!=(const Location& lhs, const Location& rhs);
