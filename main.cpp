#include <iostream>
#include "Interpreter.h"

int main(int argc, const char* argv[]) {
    Interpreter* interpreter = new Interpreter();
    vector<string> data = interpreter->lexer(argv[1]);
    try
    interpreter->parser(data);
}