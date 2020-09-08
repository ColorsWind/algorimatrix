//
// Created by colors_wind on 2020/9/8.
//

#include "ParseResult.h"

const string &ParseResult::getVariable() const {
    return variable;
}

const string &ParseResult::getMessage() const {
    return message;
}

const string &ParseResult::getSize() const {
    return size;
}

bool ParseResult::isRemove() const {
    return size.empty();
}

ParseResult::ParseResult(const string &variable, const string &message, const string &size) : variable(variable),
                                                                                              message(message),
                                                                                              size(size) {}
