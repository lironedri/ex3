#ifndef EX3_SHUNTINGYARD_H
#define EX3_SHUNTINGYARD_H
#include <bits/stdc++.h>

using namespace std;


// The class evaluate a given expression where tokens are separated by space.
class ShuntingYard {
public:
    int precedence(char op);
    int applyOp(int a, int b, char op);
    int evaluate(string tokens);


    };


#endif //EX3_SHUNTINGYARD_H
