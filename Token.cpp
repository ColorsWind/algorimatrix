//
// Created by colors_wind on 2020/8/24.
//

#include "Token.h"
#include <sstream>
using std::to_string;

string Token::toString() const {
    switch(m_type) {
        case OPERATOR:
            return string("Operator{'") + asChar() + "'}";
        case DELIMITER:
            return string("Delimiter{'") + asChar() + "'}";
        case NUMBER:
            return string("Number{") + to_string(asNumber()) + "}";
        case VARIABLE:
            return string("Variable{\"") + asString() + "\"}";
        case FUNCTION:
            return string("Function{") + asString() + "}";
        case END:
            return "END{}";
        default:
            return "Unknown";
    }
}

Token::Token(TokenType type, void *p): m_type(type), m_value(p) {}

Token::~Token() {
    if (m_value != NULL) {
        delete  m_value;
        m_value = NULL;
    }
}

Token::Token(const Token &token): m_type(token.m_type) {
    switch(token.m_type) {
        case OPERATOR:
        case DELIMITER:
            this -> m_value = new char(token.asChar());
            break;
        case NUMBER:
            this -> m_value = new double(token.asNumber());
            break;
        case VARIABLE:
        case FUNCTION:
            this -> m_value = new string(token.asString());
            break;
        case END:
        default:
            this -> m_value = NULL;
    }
}

string Token::asString() const {
    return *(string*)m_value;
}

char Token::asChar() const {
    return *(char*)m_value;
}

double Token::asNumber() const {
    return *(double*)m_value;
}

Token::Token(TokenType type, double d) : m_type(type), m_value(new double(d)){}
Token::Token(TokenType type, char c) : m_type(type), m_value(new char(c)){}
Token::Token(TokenType type, string str) : m_type(type), m_value(new string(str)){}
Token::Token(TokenType type) : m_type(type), m_value(NULL) {}

bool Token::isEquls(char c) const {
    switch (m_type) {
        case OPERATOR:
        case DELIMITER:
            if (asChar() == c) return true;
    }
    return false;
}

TokenType Token::getType() const {
    return m_type;
}
