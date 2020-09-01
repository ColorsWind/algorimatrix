//
// Created by colors_wind on 2020/9/1.
//

#include "ExtendParser.h"
#include <iostream>

using std::cerr;
using std::endl;
void ExtendParser::advance() {
    m_token = m_stream.next();
}

Token &ExtendParser::getToken(){
    return m_token;
}

double ExtendParser::processE() {
    double result = processT();
    while(m_token.getType() == OPERATOR) {
        char c = m_token.asChar();
        if (c == '+') {
            this->advance();
            result += processT();
        } else if (c == '-') {
            this->advance();
            result -= processT();
        } else {
            break;
        }
    }
    return result;
}

double ExtendParser::processT() {
    double result = processU();
    while(m_token.getType() == OPERATOR) {
        char c = m_token.asChar();
        if (c == '*') {
            this->advance();
            result *= processU();
        } else if (c == '/') {
            this->advance();
            result /= processU();
        } else {
            break;
        }
    }
    return result;
}

double ExtendParser::processU() {
    if (m_token.getType() == OPERATOR) {
        char c = m_token.asChar();
        if (c == '-') {
            this->advance();
            return -processF();
        } else if (c == '+') {
            this->advance();
            return +processF();
        }
        cerr << "ERROR processU()" << endl;
        throw;
    }
    return processF();
}

double ExtendParser::processF() {
    double result;
    if (m_token.isEquls('(')) {
        this->advance();
        result = processE();
        if (m_token.isEquls(')')) this->advance();
        else cerr << "ERROR processF() expect ')'" << endl;
    } else if (m_token.getType() == NUMBER) {
        result = m_token.asNumber();
        this-> advance();
    } else {
        cerr <<  "ERROR processF()" << endl;
        throw;
    }
    return result;
}

double ExtendParser::processL() {
    return 0;
}

ExtendParser::ExtendParser(TokenStream &tokenStream) : m_stream(tokenStream), m_token(Token(END)) {}

