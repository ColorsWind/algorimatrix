//
// Created by colors_wind on 2020/8/25.
//

#ifndef ALGORIMATRIX_STRINGTOKEN_H
#define ALGORIMATRIX_STRINGTOKEN_H


#include "Token.h"

class StringToken : public Token {
private:
    string m_value;
public:
    StringToken(TokenType type, string c);
    string toString();
};


#endif //ALGORIMATRIX_STRINGTOKEN_H
