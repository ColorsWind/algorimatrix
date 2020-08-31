//
// Created by colors_wind on 2020/8/25.
//

#ifndef ALGORIMATRIX_CHARTOKEN_H
#define ALGORIMATRIX_CHARTOKEN_H


#include "Token.h"

class CharToken : public Token {
private:
    char m_value;
public:
    CharToken(TokenType type, char c);
    string toString();
};

#endif //ALGORIMATRIX_CHARTOKEN_H
