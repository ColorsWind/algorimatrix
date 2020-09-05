//
// Created by colors_wind on 2020/8/21.
//
#include <iostream>
#include "TokenStream.h"
#include "ExtendParser.h"
#include "ParseException.h"

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
int main() {
    char ch[100];
    ExtendParser parser;
    while(true) {
        cin.getline(ch, 256);
        parser.input(ch);
        if (string(ch) == "vars") {
            parser.printVariable();
            continue;
        }
        try {
            parser.processS();
        } catch (MatrixException &exception) {
            cerr << "ERROR: matrix error:\n\t" << exception.msg() << endl;
        } catch (ParseException &exception) {
            cerr << "ERROR: parse error:\n\t" << exception.msg() << endl;
        }
    }


}

