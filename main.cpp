#include <iostream>
#include "Interpreter.h"
#include "ShuntingYard.h"

int main(int argc, const char* argv[]) {
    ShuntingYard* t =  new ShuntingYard();

    cout << t->evaluate("10 + 2 * 6") << "\n";
    cout << t->evaluate("100 * 2 + 12") << "\n";
    cout << t->evaluate("100 * ( 2 + 12 )") << "\n";
    cout << t->evaluate("100 * ( 2 + 12 ) / 14");
    Interpreter* interpreter = new Interpreter();
    vector<string> data = interpreter->lexer(argv[1]);




}