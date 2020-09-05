//
// Created by colors_wind on 2020/9/1.
//

#include "ExtendParser.h"
#include "ParseException.h"
#include <iostream>
#include <vector>
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

Matrix ExtendParser::processS() {
    this->advance();
    string variable = "ans";
    Matrix result(0,0);
    if (m_token.getType() == VARIABLE) {
        variable = m_token.asString();
        this->advance();
        if (m_token.isEquls('=')) {
            this->advance();
            result = m_matrix[variable] = processE();
        } else {
            result = m_matrix[variable];
        }
    } else {
        result = processE();
    }
    if (m_token.isEquls(';')) {
        this->advance();
    } else {
        cout << variable << " = ";
        if (result.size() > 1) cout << "\n";
        cout << result.toString() << endl;
    }
    if (m_token.getType() != END)
        throw ParseException("Expected END token, but found " + m_token.toString());
    return result;
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
        return m_matrix[str];
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
                throw;
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
    m_stream.input(str);
}



