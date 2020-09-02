//
// Created by colors_wind on 2020/8/24.
//

#include "TokenStream.h"
#include "MatrixFunc.h"

static bool isOperator(char c);
static bool isDelimiter(char c);
static bool isBlank(char c);
inline bool isDigit(char c);
inline bool isLowerCaseWord(char c);
inline bool isUpperCaseWord(char c);
inline bool isWord(char c);

TokenStream::TokenStream() {}

void TokenStream::input(string &str) {
    m_input = str;
    m_offset = 0;
    m_end = false;
}

Token TokenStream::next() {
    char c = m_input[m_offset];
    if (c == '\0') {
        m_end = true;
        return Token(END);
    } else if (isBlank(c)) {
        // skip
        m_offset++;
        return next();
    } else if (isDelimiter(c)) {
        m_offset++;
        return Token(DELIMITER, c,{c, '\0'});
    } else if (isOperator(c)) {
        m_offset++;
        return Token(OPERATOR, c, {c, '\0'});
    } else if (isWord(c)) {
        return readWord();
    } else if (isDigit(c)) {
        return readNumber();
    }
    throw "CANNOT READ TOKEN";
}
bool TokenStream::hasNext() {
    return !m_end;
}

long long TokenStream::readDigit() {
    long long result = 0;
    char c;
    while(isDigit(c = m_input[m_offset])) {
        result = 10 * result + (c - '0');
        m_offset++;
    }
    return result;
}

Token TokenStream::readNumber() {
    int begin = m_offset;
    double value;
    long long integral = readDigit();
    if (m_input[m_offset] == '.') {
        m_offset++;
        int last = m_offset;
        long long decimal = readDigit();
        value = integral + double(decimal) / pow(10, m_offset - last);
    } else {
        value = integral;
    }
    if (m_input[m_offset] == 'e' || m_input[m_offset] == 'E') {
        m_offset++;
        int exponent = readDigit();
        value *= pow(10, exponent);
    }
    return Token(NUMBER, value, m_input.substr(begin, m_offset));
}

Token TokenStream::readWord() {
    string value;
    char c;
    while(c = m_input[m_offset], isDigit(c) || isWord(c)) {
        value += c;
        m_offset++;
    }
    auto it1 = map_func1.find(value);
    if (it1 != map_func1.end()) {
        return Token(FUNCTION_1, it1 -> second, value);
    }
    auto it2 = map_func2.find(value);
    if (it2 != map_func2.end()) {
        return Token(FUNCTION_2, it2 -> second, value);
    }
    return Token(VARIABLE, value, value);
}


static bool isOperator(char c) {
    for(char i : OPERATORS) {
        if (i == c) return true;
    }
    return false;
}

static bool isDelimiter(char c) {
    for(char i : DELIMITERS) {
        if (i == c) return true;
    }
    return false;
}

static bool isBlank(char c) {
    for(char i : BLACKS) {
        if (i == c) return true;
    }
    return false;
}

bool isDigit(char c) {
    if (c >= '0' && c <= '9') {
        return true;
    }
    return false;
}

bool isLowerCaseWord(char c) {
    if (c >= 'a' && c <= 'z') {
        return true;
    }
    return false;
}

bool isUpperCaseWord(char c) {
    if (c >= 'A' && c <='a') {
        return true;
    }
    return false;
}

bool isWord(char c) {
    return isLowerCaseWord(c) || isUpperCaseWord(c) || c == '_';
}

