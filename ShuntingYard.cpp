#include "ShuntingYard.h"
#include <bits/stdc++.h>

#define SPACE 32
using namespace std;

ShuntingYard::ShuntingYard() {

}

/**
 * Function to find precedence of operators.
 * @param op
 * @return
 **/
int ShuntingYard:: precedence(char op){
    if(op == '+'||op == '-')
        return 1;
    if(op == '*'||op == '/')
        return 2;
    return 0;
}

/**
 * Function to perform arithmetic operations.
 * @param a - int
 * @param b - int
 * @param op - char operator
 * @return
 */
Expression* ShuntingYard:: applyOp(Expression* a, Expression* b, char op){
    switch(op){
        case '+': return new Plus(a,b);
        case '-': return new Minus(a,b);
        case '*': return new Mul(a,b);
        case '/':
        default:
            return new Div(a,b);
    }
}


/**
 * Function that returns value of expression after evaluation.
 * @param tokens - the give string
 * @return
 */
Expression* ShuntingYard:: evaluate(string tokens){
    // stack to store double values.
    stack <Expression*> values;

    // stack to store operators.
    stack <char> ops;

    for(size_t i = 0; i < tokens.length(); i++){

        // Current token is a whitespace, skip it.
        if(tokens.at(i) == SPACE) {
            continue;
        }

            // Current token is an opening brace, push it to 'ops'
        else if(tokens[i] == '('){
            ops.push(tokens[i]);
        }

            // Current token is a number, push it to stack for numbers.
        else if(isdigit(tokens[i])){
            double val = 0;
            double tempDouble = 0;


            // There may be more than one digits in number.
            while(i < tokens.length() && isdigit(tokens[i]))
            {
                val*=10;
                val+= (tokens.at(i) - '0');
                i++;
            }
            if(tokens[i]=='.'){
                size_t  counter = 0;
                i++;
                while (i < tokens.length() && isdigit(tokens[i])){
                    tempDouble+=(tokens.at(i) - '0');
                    counter++;
                    i++;
                }
                tempDouble/=(pow(10,counter));
                val += tempDouble;
            }
            i--;

            values.push(new Number(val));
        }

            // Closing brace encountered, solve entire brace.
        else if(tokens[i] == ')')
        {
            while(!ops.empty() && ops.top() != '(')
            {
                Expression* val2 = values.top();
                values.pop();

                Expression* val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }

            // pop opening brace.
            ops.pop();
        }

            // Current token is an operator.
        else
        {
            // While top of 'ops' has same or greater
            // precedence to current token, which
            // is an operator. Apply operator on top
            // of 'ops' to top two elements in values stack.
            while(!ops.empty() && precedence(ops.top())
                                  >= precedence(tokens[i])){
                Expression* val2 = values.top();
                values.pop();

                Expression* val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }

            // Push current token to 'ops'.
            ops.push(tokens[i]);
        }
    }

    // Entire expression has been parsed at this
    // point, apply remaining ops to remaining
    // values.
    while(!ops.empty()){
        Expression* val2 = values.top();
        values.pop();

        Expression* val1 = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(applyOp(val1, val2, op));
    }

    // Top of 'values' contains result, return it.
    return values.top();
}
