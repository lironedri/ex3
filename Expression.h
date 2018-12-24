#ifndef EX3_EXPRESSION_H
#define EX3_EXPRESSION_H

class Expression {
public:
    virtual double calculate() = 0;
    virtual ~Expression() {}
};

class Number : public Expression {
    double val;
public:
    Number(double d) {
        val = d;
    }

    double calculate() {
        return val;
    }
};

class Plus : public Expression {
    Expression* right;
    Expression* left;

public:
    Plus(Expression* l, Expression* r) {
        right = r;
        left = l;
    }

    double calculate() {
        return left->calculate() + right->calculate();
    }

};

class Mul : public Expression {
    Expression* right;
    Expression* left;

public:
    Mul(Expression* l, Expression* r) {
        this->right = r;
        this->left = l;
    }

    double calculate() {
        return left->calculate() * right->calculate();
    }

};

class Div : public Expression {
    Expression* right;
    Expression* left;

public:
    Div(Expression* l, Expression* r) {
        right = r;
        left = l;
    }

    double calculate() {
        return left->calculate() / right->calculate();
    }

};

class Minus : public Expression {
    Expression* right;
    Expression* left;

public:
    Minus(Expression* l, Expression* r) {
        right = r;
        left = l;
    }

    double calculate() {
        return left->calculate() - right->calculate();
    }

};

class Neg: public Expression {
    Expression* right;

public:
    Neg(Expression* r) {
        right = r;
    }
    double calculate() {
        return  - right->calculate();
    }

};

#endif //EX3_EXPRESSION_H