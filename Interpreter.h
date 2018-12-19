#include <iostream>
#include <vector>
#include <map>

#ifndef EX3_LEXER_H
#define EX3_LEXER_H
using namespace std;
#include "Command.h"

class Interpreter {
    map<string, Command> commandsMap;

public:
    vector<string> lexer(string fileName);
    bool stringEndsWith(const string &str, const string &toMatch);
    void parser(vector<string> data);
};


#endif //EX3_LEXER_H
