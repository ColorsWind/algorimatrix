//
// Created by colors_wind on 2020/9/1.
//

#include "ExtendParser.h"
#include <iostream>
#include <vector>
#include "MatrixFunc.h"
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

Matrix ExtendParser::processS() {
    this->advance();
    Matrix result(0,0);
    if (m_token.getType() == VARIABLE) {
        string var = m_token.asString();
        this->advance();
        if (m_token.isEquls('=')) {
            this->advance();
            result = m_matrix[var] = processE();
        } else {
            result = m_matrix[var];
        }
    } else {
        result = processE();
    }
    if (m_token.isEquls(';')) {
        this->advance();
        return Matrix(0,0);
    } else {
        return result;
    }
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
    } else if (m_token.getType() == VARIABLE) {
        string str = m_token.asString();
        this->advance();
        return m_matrix[str];
    } else if (m_token.getType() == NUMBER) {
        result = m_token.asNumber();
        this->advance();
    } else if (m_token.getType() == FUNCTION_1) {
        Func1 func = m_token.asFunction1();
        this->advance();
        if (!m_token.isEquls('(')) {
            cerr << "ERROR processF() : Expect '('" << endl;
            throw;
        }
        this->advance();
        auto expr = processL();
        result = func(expr[0]);
        if (!m_token.isEquls(')')) {
            cerr << "ERROR processF() : Expect ')'" << endl;
            throw;
        }
        this->advance();
    } else if (m_token.getType() == FUNCTION_2) {
        Func2 func = m_token.asFunction2();
        this->advance();
        if (!m_token.isEquls('(')) {
            cerr << "ERROR processF() : Expect '('" << endl;
            throw;
        }
        this->advance();
        auto expr = processL();
        result = func(expr[0], expr[1]);
        if (!m_token.isEquls(')')) {
            cerr << "ERROR processF() : Expect ')'" << endl;
            throw;
        }
        this->advance();
    } else {
        cerr <<  "ERROR processF() : Unexpected Token " << m_token.toString() << endl;
        throw;
    }
    return result;
}

vector<Matrix> ExtendParser::processL() {
    vector<Matrix> arr;
    arr.push_back(processE());
    while(m_token.isEquls(',')) {
        this->advance();
        arr.push_back(processE());
    }
    return arr;
}

Matrix ExtendParser::processM()
{
    vector<vector<Matrix>> arr;
    arr.push_back(processL());
    while(m_token.isEquls(';')) {
        this->advance();
        arr.push_back(processL());
    }
    int row = arr.size();
    int col = arr.front().size();
    Matrix matrix(row, col);
    for(int i=0;i<row;i++) {
        vector<Matrix> &line = arr[i];
        if (line.size() != col) {
            cerr << "ERROR processM() : Inconsistent number of elements in row vector.";
            throw;
        }
        for(int j=0;j<col;j++)
            matrix.at(i, j) = line[j][0];
    }
    return matrix;
}


ExtendParser::ExtendParser() : m_stream(TokenStream()), m_token(Token(END)) {}

void ExtendParser::input(string str) {
    m_token = Token(END);
    m_stream.input(str);
}



