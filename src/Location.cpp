#include "Location.h"

Location::Location(const char& letter, const int& num) : m_letter(letter), m_num(num) {}

Location::Location(const Location& other) : m_letter(other.m_letter), m_num(other.m_num) {}

Location& Location::operator=(const Location& other) {
    m_letter = other.m_letter;
    m_num = other.m_num;
    return *this;
}

const bool Location::operator==(const Location& other) const {
    return m_letter == other.m_letter && m_num == other.m_num;
}

const bool Location::operator!=(const Location& other) const {
    return !(*this == other);
}

Location Location::operator+(const Location& other) const {
    return Location(m_letter + other.m_letter, m_num + other.m_num);
}

Location Location::operator-(const Location& other) const {
    return Location(m_letter - other.m_letter, m_num - other.m_num);
}

const bool Location::operator<(const Location& other) const {
    if (m_letter < other.m_letter)
        return true;
    else if (m_letter == other.m_letter)
        return m_num < other.m_num;
    else
        return false;
}

const bool Location::operator>(const Location& other) const {
    if (m_letter > other.m_letter)
        return true;
    else if (m_letter == other.m_letter)
        return m_num > other.m_num;
    else
        return false;
}
