//
// Created by colors_wind on 2020/8/21.
//
#include <iostream>
#include "TokenStream.h"
#include "ExtendParser.h"
using namespace std;
int main() {
    char a[100];
    cin.getline(a, 100);
    string command(a);
    TokenStream tokenStream(command);
    ExtendParser parser(tokenStream);
    parser.advance();
    Matrix matrix = parser.processE();
    if (parser.getToken().getType() != END) {
        cerr << "ERROR not end";
    }
    cout << "ANS = ";
    if (matrix.size() > 1) {
        cout << "\n";
    }
    cout << matrix.toString() << endl;
}

