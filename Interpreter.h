#ifndef EX3_LEXER_H
#define EX3_LEXER_H

#include <iostream>
#include <vector>
#include <map>
#include "Command.h"

using namespace std;


class Interpreter {

public:
    vector<string> lexer(string fileName);
    bool stringEndsWith(const string &str, const string &toMatch);
    void parser(vector<string> data);
    map<string, Expression*> createCommandsMap(vector<string> dataVec, int index);
};


#endif //EX3_LEXER_H
