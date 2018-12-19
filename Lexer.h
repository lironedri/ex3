#include <iostream>
#include <vector>
#ifndef EX3_LEXER_H
#define EX3_LEXER_H
using namespace std;

class Lexer {
public:
    vector<string> doLexer(string fileName);
    bool stringEndsWith(const string &str, const string &toMatch);
};


#endif //EX3_LEXER_H
