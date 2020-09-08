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

string ExtendParser::processS() {
    string output;
    this->advance();
    Matrix result(0,0);
    string variable = m_token.asString();
    this->advance();
    if (m_token.isEquls('=')) {
        this->advance();
        result = m_matrix[variable] = processE();
    } else {
        result = m_matrix[variable];
    }
    if (m_token.isEquls(';')) {
        this->advance();
    } else {
        output.append(variable).append(" = ");
        if (result.size() > 1) output.append("\n");
        output.append(result.toString());
    }
    if (m_token.getType() != END)
        throw ParseException("Expected END token, but found " + m_token.toString());
    return output;
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

Matrix ExtendParser::processM() {
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
        str.insert(0, "ans = ");
    m_stream.input(str);
}

using std::setw;
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



