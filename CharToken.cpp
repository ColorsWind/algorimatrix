//
// Created by colors_wind on 2020/8/25.
//

#include "CharToken.h"

using std::string;
string CharToken::toString() {
    string type_name;
    switch(m_type) {
        case DELIMITER:
            type_name = "Delimiter";
            break;
        case OPERATOR:
            type_name = "Operator";
            break;
        default:
            type_name = "Unknown";

    }
    return "Type: " + type_name + ", Value: " + m_value;
}

CharToken::CharToken(TokenType type, char c) : Token(type), m_value(c) {}