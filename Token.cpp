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
        switch(m_type) {
            case OPERATOR:
            case DELIMITER:
                delete (char*)m_value;
                break;
            case NUMBER:
                delete (double *)m_value;
                break;
            case VARIABLE:
            case FUNCTION:
                delete (string*)m_value;
                break;
        }
        m_value = NULL;
    }
}

Token &Token::operator=(const Token &token) {
    this ->m_type = token.m_type;
    this ->m_value = token.copyValue();
    return *this;
}


Token::Token(const Token & token): m_type(token.m_type), m_value(token.copyValue()) {}

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

void *Token::copyValue() const {
    switch(m_type) {
        case OPERATOR:
        case DELIMITER:
            return new char(asChar());
        case NUMBER:
            return new double(asNumber());
        case VARIABLE:
        case FUNCTION:
            return new string(asString());
        case END:
        default:
            return NULL;
    }
}

