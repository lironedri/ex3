#include <iostream>
#include "Lexer.h"

int main(int argc, const char* argv[]) {
    Lexer* lex = new Lexer();
    vector<string> data = lex->doLexer(argv[1]);
    for(int i = 0; i < data.size(); i++){
        cout << data[i] << endl;
    }
}