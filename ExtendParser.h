//
// Created by colors_wind on 2020/9/1.
//

#ifndef ALGORIMATRIX_EXTENDPARSER_H
#define ALGORIMATRIX_EXTENDPARSER_H

#include <iostream>
#include <map>
#include "TokenStream.h"
#include "Matrix.h"
#include "Token.h"
#include "ParseResult.h"
using std::string;
using std::map;

const static string ANS = "ans";
// E -> T{(+|-)T}
// T -> U{(*|/)U}
// U -> -F | +F | F
// F -> (E) | FUNCTION_1(L) | VARIABLE | [L] | NUMBER
// L  -> E{,E}
class ExtendParser {
protected:
    TokenStream m_stream;
    Token m_token;
    map<string, Matrix> m_matrix;
public:
    ExtendParser ();
    void advance();
    Token & getToken();
    ParseResult processS();
    Matrix processE();
    Matrix processT();
    Matrix processU();
    Matrix processF();
    vector<struct Matrix> processL();
    Matrix processM();
    void input(string basicString);

    void printVariable();
};


#endif //ALGORIMATRIX_EXTENDPARSER_H
