//
// Created by colors_wind on 2020/9/8.
//

#include "ParseResult.h"

const string &ParseResult::getVariable() const {
    return m_variable;
}

const string &ParseResult::getMessage() const {
    return m_message;
}

const string &ParseResult::getSize() const {
    return m_size;
}

bool ParseResult::isRemove() const {
    return m_size.empty();
}

const string &ParseResult::getCommand() const {
    return m_command;
}

ParseResult::ParseResult(const string &command, const string &variable, const string &message, const string &size) :
                                                                                              m_command(command),
                                                                                              m_variable(variable),
                                                                                              m_message(message),
                                                                                              m_size(size) {}

ParseResult::ParseResult() {}
