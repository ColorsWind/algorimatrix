//
// Created by colors_wind on 2020/9/1.
//

#include "ExtendParser.h"
#include <iostream>
#include <vector>

using std::cerr;
using std::endl;
using std::vector;
using std::copy;
void ExtendParser::advance() {
    m_token = m_stream.next();
}

Token &ExtendParser::getToken(){
    return m_token;
}

 Matrix ExtendParser::processE() {
    Matrix result = processT();
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

Matrix ExtendParser::processT() {
    Matrix result = processU();
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

Matrix ExtendParser::processU() {
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

Matrix ExtendParser::processF() {
    Matrix result(0, 0);
    if (m_token.isEquls('(')) {
        this->advance();
        result = processE();
        if (m_token.isEquls(')')) this->advance();
        else cerr << "ERROR processF() : Expect ')'" << endl;
    } else if (m_token.isEquls('[')) {
        this->advance();
        result = processM();
        if (m_token.isEquls(']')) this->advance();
        else cerr << "ERROR processF() : Expect ']'" << endl;
    } else if (m_token.getType() == NUMBER) {
        result = m_token.asNumber();
        this-> advance();
    } else {
        cerr <<  "ERROR processF() : Unexpected Token " << m_token.toString() << endl;
        throw;
    }
    return result;
}

Matrix ExtendParser::processL() {
    vector<double> arr;
    arr.push_back(processE()[0]);
    while(m_token.isEquls(',')) {
        this->advance();
        arr.push_back(processE()[0]);
    }
    return Matrix(arr);
}

Matrix ExtendParser::processM()
{
    vector<Matrix> arr;
    arr.push_back(processL());
    while(m_token.isEquls(';')) {
        this->advance();
        arr.push_back(processL());
    }
    int row = arr.size();
    int col = arr.front().getCol();
    Matrix matrix(arr.size(), arr.front().getCol());
    for(int i=0;i<row;i++) {
        Matrix &line = arr[i];
        if (line.getCol() != col) {
            cerr << "ERROR processM() : Inconsistent number of elements in row vector.";
            throw;
        }
        for(int j=0;j<col;j++)
            matrix.at(i, j) = line.read(0, j);
    }
    return matrix;
}


ExtendParser::ExtendParser(TokenStream &tokenStream) : m_stream(tokenStream), m_token(Token(END)) {}


