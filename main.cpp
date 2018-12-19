#include <iostream>
#include "Interpreter.h"

int main(int argc, const char* argv[]) {
    Interpreter* lex = new Interpreter();
    vector<string> data = lex->lexer(argv[1]);
    for(int i = 0; i < data.size(); i++){
        cout << data[i] << endl;
    }
}