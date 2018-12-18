//
// Created by liron and Dekel on 12/16/18.
//
#include <iostream>
#include <vector>
#ifndef EX3_LEXER_H
#define EX3_LEXER_H
using namespace std;

class Lexer {
public:
    virtual vector<string> doLexer(string fileName);
};


#endif //EX3_LEXER_H
