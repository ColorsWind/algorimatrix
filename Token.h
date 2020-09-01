  //
// Created by colors_wind on 2020/8/24.
//

#ifndef ALGORIMATRIX_TOKEN_H
#define ALGORIMATRIX_TOKEN_H
#include <iostream>
using std::string;
using std::ostream;
const static char OPERATORS[] = {'+', '-', '*', '/'};
const static char DELIMITERS[] = {'(', ')', '[', ']', ',', ';'};
const static string BLACKS = {' ', '\r', '\n', '\f'};


enum TokenType {VARIABLE, NUMBER, FUNCTION, OPERATOR, DELIMITER, END};
class Token {
protected:
    TokenType m_type;
    void* m_value;
public:
    explicit Token(TokenType type);
    Token & operator=(const Token & token);
    Token(TokenType type, double d);
    Token(TokenType type, char c);
    Token(TokenType type, string str);
    Token(TokenType type, void* p);
    ~Token();
    Token(const Token & token);
    string asString() const;
    char asChar() const;
    double asNumber() const;
    string toString() const;
    bool isEquls(char c) const;
    TokenType getType() const;
    void* copyValue() const;

};

#endif //ALGORIMATRIX_TOKEN_H
