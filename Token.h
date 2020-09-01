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
const static string BLACKS = {' '};


enum TokenType {VARIABLE, NUMBER, FUNCTION, OPERATOR, DELIMITER, END};
class Token {
protected:
    const TokenType m_type;
    void* m_value;
public:
    Token(TokenType type, void* p);
    ~Token();
    Token(const Token & token);
    string asString() const;
    char asChar() const;
    double asNumber() const;
    string toString() const;
};

#endif //ALGORIMATRIX_TOKEN_H
