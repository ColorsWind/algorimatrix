//
// Created by colors_wind on 2020/8/25.
//

#ifndef ALGORIMATRIX_NUMBERTOKEN_H
#define ALGORIMATRIX_NUMBERTOKEN_H


#include "Token.h"

class NumberToken : public Token {
private:
    double m_value;
public:
    NumberToken(TokenType type, double d);
    string toString();
};


#endif //ALGORIMATRIX_NUMBERTOKEN_H
