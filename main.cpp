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
    while(tokenStream.hasNext()) {
        cout << tokenStream.next().toString() << endl;
    }

}

