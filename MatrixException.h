//
// Created by colors_wind on 2020/9/5.
//

#ifndef ALGORIMATRIX_MATRIXEXCEPTION_H
#define ALGORIMATRIX_MATRIXEXCEPTION_H

#include <iostream>
#include <exception>

using std::exception;
using std::string;
class MatrixException : public exception {
private:
    string m_msg;
public:
    MatrixException(string msg);
    string & msg();
    const char * what () const throw () {
        return "Matrix calculation exception";
    }
};


#endif //ALGORIMATRIX_MATRIXEXCEPTION_H
