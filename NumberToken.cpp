//
// Created by colors_wind on 2020/8/25.
//

#include "NumberToken.h"
#include <string>

using std::to_string;
NumberToken::NumberToken(TokenType type, double d) : Token(type), m_value(d) {}

string NumberToken::toString() {
    return "Type: Number, Value:" + to_string(m_value);
}