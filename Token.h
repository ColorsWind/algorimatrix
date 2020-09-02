  //
// Created by colors_wind on 2020/8/24.
//

#ifndef ALGORIMATRIX_TOKEN_H
#define ALGORIMATRIX_TOKEN_H
#include <iostream>
#include "Matrix.h"

using std::string;
using std::ostream;
const static char OPERATORS[] = {'+', '-', '*', '/', '='};
const static char DELIMITERS[] = {'(', ')', '[', ']', ',', ';'};
const static string BLACKS = {' ', '\r', '\n', '\f'};


enum TokenType {VARIABLE, NUMBER, FUNCTION_1, FUNCTION_2, OPERATOR, DELIMITER, END};
class Token {
protected:

    TokenType m_type;
    void* m_value;
    string m_origin;
public:
    Token(TokenType type, const string &origin="\0");
    Token & operator=(const Token & token);
    Token(TokenType type, double d, const string &origin);
    Token(TokenType type, char c, const string &origin);
    Token(TokenType type, string str, const string &origin);
    Token(TokenType type, void* p, const string &origin);
    ~Token();
    Token(const Token & token);
    string asString() const;
    char asChar() const;
    double asNumber() const;
    string toString() const;
    bool isEquls(char c) const;
    TokenType getType() const;
    void* copyValue() const;
    Func1 asFunction1() const;
    Func2 asFunction2() const;
    const string &getRawText() const;

    Token(TokenType type, Func1 p, const string &origin);
};

#endif //ALGORIMATRIX_TOKEN_H
