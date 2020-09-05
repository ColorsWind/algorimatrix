//
// Created by colors_wind on 2020/9/5.
//

#include "ParseException.h"

ParseException::ParseException(string msg) : m_msg(msg) {}

string &ParseException::msg() {
    return m_msg;
}