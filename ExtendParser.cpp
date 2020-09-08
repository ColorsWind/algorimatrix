//
// Created by colors_wind on 2020/9/1.
//

#include "ExtendParser.h"
#include "ParseException.h"
#include <iostream>
#include <vector>
#include <iomanip>

using std::cout;
using std::endl;
using std::vector;
using std::copy;
using std::setw;

void ExtendParser::advance() {
    if (m_stream.hasNext()) {
        m_token = m_stream.next();
    } else {
        throw ParseException("No more token");
    }

}

Token &ExtendParser::getToken(){
    return m_token;
}

ParseResult ExtendParser::processS() {
    Matrix matrix(0, 0);
    string message;
    string size;
    this->advance();
    string variable = m_token.asString();
    this->advance();
    // matrix
    if (m_token.isEquls('=')) {
        this->advance();
        matrix = processE();
    } else {
        throw ParseException("Expected '=', but found " + m_token.toString());
    }
    // message
    if (m_token.isEquls(';')) {
        this->advance();
    } else {
        message.append(variable).append(" = ");
        if (matrix.size() > 1) message.append("\n");
        message.append(matrix.toString());
    }
    // variable & size
    if (variable == ANS || matrix.size() > 0) {
        m_matrix[variable] = matrix;
        size = matrix.sizeString();
    } else {
        m_matrix.erase(variable);
    }
    if (m_token.getType() != END)
        throw ParseException("Expected END token, but found " + m_token.toString());
    return ParseResult(variable, message, size);
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
        throw ParseException("Unexpected operator " + to_string(c));
    }
    return processF();
}

Matrix ExtendParser::processF() {
    Matrix result(0, 0);
    if (m_token.isEquls('(')) {
        this->advance();
        result = processE();
        if (m_token.isEquls(')')) {
            this->advance();
        } else {
            throw ParseException("Expect ')' but " + m_token.toString());
        }
    } else if (m_token.isEquls('[')) {
        this->advance();
        result = processM();
        if (m_token.isEquls(']')) {
            this->advance();
        } else {
            throw ParseException("Expect ']' but " + m_token.toString());
        }
    } else if (m_token.getType() == VARIABLE) {
        string str = m_token.asString();
        this->advance();
        auto iter = m_matrix.find(str);
        if (iter == m_matrix.end())
            return Matrix(0,0);
        else
            return iter->second;
    } else if (m_token.getType() == NUMBER) {
        result = Matrix(m_token.asNumber());
        this->advance();
    } else if (m_token.getType() == FUNCTION) {
        Func func = m_token.asFunction();
        this->advance();
        if (m_token.isEquls('(')) {
            this->advance();
            auto expr = processL();
            result = func(expr);
            if (m_token.isEquls(')')) {
                this->advance();
            } else {
                throw ParseException("Expect ')' but " + m_token.toString());
            }
        } else {
            result = Matrix(0,0);
        }

    } else {
        throw ParseException("Unexpect token " + m_token.toString());
    }
    return result;
}

vector<Matrix> ExtendParser::processL() {
    if (m_token.isEquls(')')) return vector<Matrix>();
    vector<Matrix> arr;
    arr.push_back(processE());
    while(m_token.isEquls(',')) {
        this->advance();
        arr.push_back(processE());
    }
    return arr;
}

Matrix ExtendParser::processM() {
    if (m_token.isEquls(']')) return Matrix(0,0);
    vector<vector<Matrix>> arr;
    arr.push_back(processL());
    while(m_token.isEquls(';')) {
        this->advance();
        arr.push_back(processL());
    }
    ObjectMatrix<Matrix> block(arr);
    return fromBlock(block);
}


ExtendParser::ExtendParser() : m_stream(TokenStream()), m_token(Token(END)) {}

void ExtendParser::input(string str) {
    m_token = Token(END);
    if (str.find('=') == string::npos)
        str.insert(0, ANS + " = ");
    m_stream.input(str);
}

void ExtendParser::printVariable() {
    int width = 10;
    for(auto iter = m_matrix.begin(); iter != m_matrix.end(); iter++) {
        if (iter -> first.size() > width)
            width = iter -> first.size();
    }
    for(int k=0;k<width+10;k++) cout << "-";
    cout << endl;
    cout << "|" << setw(width) << "Name" << "|" << setw(7) << "Size" << "|" << endl;
    for(int k=0;k<width+10;k++) cout << "-";
    cout << endl;
    for(auto iter = m_matrix.begin(); iter != m_matrix.end(); iter++) {
        cout << "|" << setw(width) << iter -> first << "|"  << setw(7) << iter->second.sizeString() << "|" << endl;
    }
    for(int k=0;k<width+10;k++) cout << "-";
    cout << endl;
}



