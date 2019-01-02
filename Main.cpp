#include <iostream>
#include "Interpreter.h"
#include "ShuntingYard.h"
#include "Server.h"
#include "SocketWriteRead.h"
#include "Client.h"
#include "SymbolTable.h"

int main(int argc, const char *argv[]) {
    Interpreter* interpreter = new Interpreter();
    vector<string> data = interpreter->lexer(argv[1]);
    interpreter->parser(data);
    pthread_exit(NULL);
}

