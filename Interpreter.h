#ifndef EX3_LEXER_H
#define EX3_LEXER_H

#include <iostream>
#include <vector>
#include <map>
#include "Expression.h"
using namespace std;

class Interpreter {

public:
    vector<string> lexer(string fileName);
    bool stringEndsWith(const string &str, const string &toMatch);
    void parser(vector<string> data);
    bool stringStartsWith(const string haystack, const string& needle);
    vector<string> lineLexer(string s);
    };


#endif //EX3_LEXER_H
