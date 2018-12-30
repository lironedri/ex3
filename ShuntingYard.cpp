#define SPACE 32
#define OPEN_BRACKET 40
#define CLOSE_BRACKET 41

#include "ShuntingYard.h"
#include <bits/stdc++.h>

using namespace std;

ShuntingYard::ShuntingYard(SymbolTable *symbolTable) {
    this->m_symbolTable = symbolTable;
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

/*
 * the function gets a string which describes an expression and calculates
 * it using applyOperation method.
 */
Expression *ShuntingYard::evaluate(string tokens) {
    bool minusOp = false;
    //contains all the operation
    stack<char> operations;
    //contains all the values
    stack<Expression *> numbers;
    //running over each char of the given tokens
    for (int index = 0; index < tokens.length(); index++) {
        if (tokens.at(index) == SPACE) {
            continue;
            //if the current char is '(' - push it to operations.
        } else if (tokens.at(index) == OPEN_BRACKET) {
            operations.push(tokens.at(index));
            //if the current char is a digit - push it to operations.
        } else if (isdigit(tokens.at(index))) {
            //will hold the current number which is consists of the current
            // chars.
            double temp = 0;
            double tempDecimal = 0;
            int exponent = 1;
            minusOp = true;
            //turns a string that consists of numbers into an integer.
            while (index < tokens.length() &&
                   isdigit(tokens.at(index))) {
                temp *= 10;
                temp += (tokens.at(index) - '0');
                index++;
            }
            //implements shunting yard on decimal numbers
            if (index < tokens.length() && tokens.at(index) == '.') {
                index++;
                while (index < tokens.length() && isdigit(tokens.at
                        (index))) {
                    tempDecimal += ((double) (tokens.at(index) - '0') /
                                    pow(10, exponent));
                    exponent++;
                    index++;
                }
                temp += tempDecimal;
            }
            index--;
            //push the number to the numbers' stack
            numbers.push(new Number(temp));
            //if the current char is ')' - push it to the stack, solve what's
            // inside the braces
        } else if (tokens.at(index) == CLOSE_BRACKET) {
            //calculate all the operations in the stack operations until
            // we face '('
            while (operations.top() != OPEN_BRACKET && !operations.empty()) {
                Expression *val2 = numbers.top();
                numbers.pop();
                Expression *val = numbers.top();
                numbers.pop();
                char operation = operations.top();
                operations.pop();
                numbers.push(applyOp(val, val2, operation));
            }
            operations.pop();
            //checks if it is one of the operators - +,-,/,*
        } else if (precedence(tokens[index]) != 0) {
            //if the current minus is not a binary tokens, but unary
            if (!minusOp) {
                Expression *zeroNum = new Number(0);
                numbers.push(zeroNum);
            }
            /* while the top operation of the operations stack has same or greater precedence
            to the current operation, apply that operation. */
            while (!operations.empty() && minusOp && (precedence (tokens.at(index)) <=
                                                      precedence(operations.top()))) {
                Expression *val2 = numbers.top();
                numbers.pop();
                Expression *val = numbers.top();
                numbers.pop();
                char operation = operations.top();
                operations.pop();
                numbers.push(applyOp(val, val2, operation));
            }
            operations.push(tokens.at(index));
            minusOp = false;
        } else {
            string varName = "";
            minusOp = true;
            // while the token is not operator or number
            while (precedence(tokens[index]) == 0 &&
                   index < tokens.length() &&
                   tokens.at(index) != CLOSE_BRACKET) {
                // the first letter is not a number and not operator
                if (tokens.at(index) != SPACE) {
                    varName += tokens[index];
                }
                index += 1;
            }
            Expression* variableValue = new Number(this->m_symbolTable->getVarValue(varName));
            numbers.push(variableValue);
            index -= 1;
        }
    }
    /* after the whole tokens has been parsed, apply the remaining
    operations with to remaining values */
    while (!operations.empty()) {
        Expression *val2 = numbers.top();
        numbers.pop();
        Expression *val = numbers.top();
        numbers.pop();
        char operation = operations.top();
        operations.pop();
        numbers.push(applyOp(val, val2, operation));
    }
    return numbers.top();
}


//#include "ShuntingYard.h"
//#include <bits/stdc++.h>
//
//#define SPACE 32
//using namespace std;
//
//ShuntingYard::ShuntingYard() {
//
//}
//
///**
// * Function to find precedence of operators.
// * @param op
// * @return
// **/
//int ShuntingYard:: precedence(char op){
//    if(op == '+'||op == '-')
//        return 1;
//    if(op == '*'||op == '/')
//        return 2;
//    return 0;
//}
//
///**
// * Function to perform arithmetic operations.
// * @param a - int
// * @param b - int
// * @param op - char operator
// * @return
// */
//Expression* ShuntingYard:: applyOp(Expression* a, Expression* b, char op){
//    switch(op){
//        case '+': return new Plus(a,b);
//        case '-': return new Minus(a,b);
//        case '*': return new Mul(a,b);
//        case '/':
//        default:
//            return new Div(a,b);
//    }
//}
//
//
///**
// * Function that returns value of expression after evaluation.
// * @param tokens - the give string
// * @return
// */
//Expression* ShuntingYard:: evaluate(string tokens){
//    // stack to store double values.
//    stack <Expression*> values;
//
//    // stack to store operators.
//    stack <char> ops;
//
//    for(size_t i = 0; i < tokens.length(); i++){
//
//        // Current token is a whitespace, skip it.
//        if(tokens.at(i) == SPACE) {
//            continue;
//        }
//
//            // Current token is an opening brace, push it to 'ops'
//        else if(tokens[i] == '('){
//            ops.push(tokens[i]);
//        }
//
//            // Current token is a number, push it to stack for numbers.
//        else if(isdigit(tokens[i])){
//            double val = 0;
//            double tempDouble = 0;
//
//
//            // There may be more than one digits in number.
//            while(i < tokens.length() && isdigit(tokens[i]))
//            {
//                val*=10;
//                val+= (tokens.at(i) - '0');
//                i++;
//            }
//            if(tokens[i]=='.'){
//                size_t  counter = 0;
//                i++;
//                while (i < tokens.length() && isdigit(tokens[i])){
//                    tempDouble+=(tokens.at(i) - '0');
//                    counter++;
//                    i++;
//                }
//                tempDouble/=(pow(10,counter));
//                val += tempDouble;
//            }
//            i--;
//
//            values.push(new Number(val));
//        }
//
//            // Closing brace encountered, solve entire brace.
//        else if(tokens[i] == ')')
//        {
//            while(!ops.empty() && ops.top() != '(')
//            {
//                Expression* val2 = values.top();
//                values.pop();
//
//                Expression* val1 = values.top();
//                values.pop();
//
//                char op = ops.top();
//                ops.pop();
//
//                values.push(applyOp(val1, val2, op));
//            }
//
//            // pop opening brace.
//            ops.pop();
//        }
//
//            // Current token is an operator.
//        else
//        {
//            // While top of 'ops' has same or greater
//            // precedence to current token, which
//            // is an operator. Apply operator on top
//            // of 'ops' to top two elements in values stack.
//            while(!ops.empty() && precedence(ops.top())
//                                  >= precedence(tokens[i])){
//                Expression* val2 = values.top();
//                values.pop();
//
//                Expression* val1 = values.top();
//                values.pop();
//
//                char op = ops.top();
//                ops.pop();
//
//                values.push(applyOp(val1, val2, op));
//            }
//
//            // Push current token to 'ops'.
//            ops.push(tokens[i]);
//        }
//    }
//
//    // Entire expression has been parsed at this
//    // point, apply remaining ops to remaining
//    // values.
//    while(!ops.empty()){
//        Expression* val2 = values.top();
//        values.pop();
//
//        Expression* val1 = values.top();
//        values.pop();
//
//        char op = ops.top();
//        ops.pop();
//
//        values.push(applyOp(val1, val2, op));
//    }
//
//    // Top of 'values' contains result, return it.
//    return values.top();
//}
