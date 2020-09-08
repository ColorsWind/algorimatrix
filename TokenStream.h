//
// Created by colors_wind on 2020/8/24.
//

#ifndef ALGORIMATRIX_TOKENSTREAM_H
#define ALGORIMATRIX_TOKENSTREAM_H

#include <iostream>
#include "Token.h"

using std::string;
class TokenStream {
private:
    string m_input;
    int m_offset{};
    bool m_end{};
    Token readNumber();
    Token readWord();
public:
    TokenStream();
    bool hasNext() const;
    Token next();

    long long int readDigit();

    void input(string &str);
};


#endif //ALGORIMATRIX_TOKENSTREAM_H
