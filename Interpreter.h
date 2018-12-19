#include <iostream>
#include <vector>
#ifndef EX3_LEXER_H
#define EX3_LEXER_H
using namespace std;
#include "Command.h"

class Interpreter {
public:
    vector<string> lexer(string fileName);
    bool stringEndsWith(const string &str, const string &toMatch);
    Command parser(string commandStr);
};


#endif //EX3_LEXER_H
