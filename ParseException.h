//
// Created by colors_wind on 2020/9/5.
//

#ifndef ALGORIMATRIX_PARSEEXCEPTION_H
#define ALGORIMATRIX_PARSEEXCEPTION_H
#include <iostream>

using std::string;
using std::exception;

class ParseException : public exception {
private:
    string m_msg;
public:
    explicit ParseException(const string & msg);
    string & msg();
    const char * what () const noexcept {
        return "Expression parsing exception";
    }
};


#endif //ALGORIMATRIX_PARSEEXCEPTION_H
