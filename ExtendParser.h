//
// Created by colors_wind on 2020/9/1.
//

#ifndef ALGORIMATRIX_EXTENDPARSER_H
#define ALGORIMATRIX_EXTENDPARSER_H

#include <iostream>
#include "TokenStream.h"
#include "Matrix.h"
#include "Token.h"
using std::string;

// E -> T{(+|-)T}
// T -> U{(*|/)U}
// U -> -F | +F | F
// F -> (E) | FUNCTION(L) | VARIABLE | [L] | NUMBER
// L  -> E{,E}
class ExtendParser {
private:
    TokenStream m_stream;
    Token m_token;
public:
    ExtendParser(TokenStream & tokenStream);
    void advance();
    Token & getToken();
    Matrix processE();
    Matrix processT();
    Matrix processU();
    Matrix processF();
    Matrix processL();


    Matrix processM();
};


#endif //ALGORIMATRIX_EXTENDPARSER_H
