#ifndef EX3_BINARYEXPRESSION_H
#define EX3_BINARYEXPRESSION_H


#include "Expression.h"

class BinaryExpression : public Expression {
    Expression* left;
    Expression* right;
public:
    BinaryExpression(Expression* left, Expression* right);
    virtual double calculate() = 0;
    Expression* getLeftExp(){
        return this->left;
    }
    Expression* getRightExp(){
        return this->right;
    }


};


#endif //EX3_BINARYEXPRESSION_H
