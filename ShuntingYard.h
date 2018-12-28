#ifndef EX3_SHUNTINGYARD_H
#define EX3_SHUNTINGYARD_H

#include <bits/stdc++.h>
#include "Expression.h"
using namespace std;

// The class evaluate a given expression where tokens are separated by space.
class ShuntingYard {
public:
    ShuntingYard();
    int precedence(char op);
    Expression* applyOp(Expression* a, Expression* b, char op);
    Expression* evaluate(string tokens);


};


#endif //EX3_SHUNTINGYARD_H
