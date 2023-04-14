#pragma once

class Location {
public:
    Location(const char& letter = 'a', const int& num = 0);
    Location(const Location& other);
    Location& operator=(const Location& other);
    const bool operator==(const Location& other) const;
    const bool operator!=(const Location& other) const;
    Location operator+(const Location& other) const;
    Location operator-(const Location& other) const;
    const bool operator<(const Location& other) const;
    const bool operator>(const Location& other) const;
    char getLetter() const { return m_letter; }
    int getNum() const { return m_num; }
private:
    char m_letter;
    int m_num;
};


