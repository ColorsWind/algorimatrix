//
// Created by colors_wind on 2020/9/8.
//

#ifndef ALGORIMATRIX_PARSERESULT_H
#define ALGORIMATRIX_PARSERESULT_H

#include <iostream>
using std::string;
class ParseResult {
private:
    string m_command;
    string m_variable;
    string m_message;
    string m_size;
public:
    ParseResult();
    ParseResult(const string &command, const string &variable, const string &message, const string &size);
    const string &getCommand() const;
    const string &getVariable() const;
    const string &getMessage() const;
    const string &getSize() const;
    bool isRemove() const;
};


#endif //ALGORIMATRIX_PARSERESULT_H
