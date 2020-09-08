//
// Created by colors_wind on 2020/9/5.
//

#include "MatrixException.h"

MatrixException::MatrixException(const string &msg) : m_msg(msg) {}

string &MatrixException::msg() {
    return m_msg;
}
