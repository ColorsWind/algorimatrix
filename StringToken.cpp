//
// Created by colors_wind on 2020/8/25.
//

#include "StringToken.h"
string StringToken::toString() {
    string type_name;
    switch(m_type) {
        case VARIABLE:
            type_name = "Variable";
            break;
        case FUNCTION:
            type_name = "Function";
        default:
            type_name = "Unknown";
    }
    return "Type: " + type_name + ", Value: " + m_value;
}

StringToken::StringToken(TokenType type, string str): Token(type), m_value(str) {}
