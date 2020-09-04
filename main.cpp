//
// Created by colors_wind on 2020/8/21.
//
#include <iostream>
#include "TokenStream.h"
#include "ExtendParser.h"

using namespace std;
int main() {
    char a[100];
    string command;
    ExtendParser parser;
    while(true) {
        cin.getline(a, 100);
        command = a;
        parser.input(command);
        Matrix matrix = parser.processS();
        if (parser.getToken().getType() != END) {
            cerr << "ERROR not end";
        }
        cout << "ANS = ";
        if (matrix.size() > 1) {
            cout << "\n";
        }
        cout << matrix.toString() << endl;
    }


}

