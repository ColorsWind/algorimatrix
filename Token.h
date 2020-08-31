  //
// Created by colors_wind on 2020/8/24.
//

#ifndef ALGORIMATRIX_TOKEN_H
#define ALGORIMATRIX_TOKEN_H
#include <iostream>
using std::string;
using std::ostream;
const static char OPERATORS[] = {'+', '-', '*', '/'};
const static char DELIMITERS[] = {'(', ')', '[', ']', ','};
const static string BLACKS = {' ', '\r', '\n', '\f'};


enum TokenType {VARIABLE, NUMBER, FUNCTION, OPERATOR, DELIMITER, END};
class Token {
protected:
    TokenType m_type;
public:
    Token(TokenType type);
    virtual string toString();
};

#endif //ALGORIMATRIX_TOKEN_H
