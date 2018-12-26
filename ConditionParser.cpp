#include "ConditionParser.h"

int ConditionParser::execute(vector<string> data, int index) {
    double leftOperand, rightOperand;
    //left operand
    if(this->m_dataBase.isVarValueExist(data[index + 1])){
        leftOperand = this->m_dataBase.getVarValue(data[index + 1]);
        //in case the var is a number (given as a string) and not a known var from the map
    } else {
        string::size_type sz;
        leftOperand = stod(data[index + 1], &sz);

    }

    //right operand
    if(this->m_dataBase.isVarValueExist(data[index + 3])){
        rightOperand = this->m_dataBase.getVarValue(data[index + 3]);
        //in case the var is a number (given as a string) and not a known var from the map
    } else {
        string::size_type sz;
        rightOperand = stod(data[index + 3], &sz);
    }

    //check the condition
    if (this->m_dataBase.g)
}

/**
 * the function gets operator as a char, in case we can convert the operator to one char
 * and returns a boolean value of the expression answer.
 * @param leftOperand
 * @param op
 * @param rightOperand
 * @return
 */
bool ConditionParser::conditionSwitchCase(double leftOperand, double rightOperand, char op){
    switch (op){
        case '<':
            return leftOperand < rightOperand;
        case '>':
            return leftOperand > rightOperand;
        case '=':
            return leftOperand == rightOperand;
    }
}

/**
 * the gets a string operator and returns the bool value of the condition by using the switch-case by char function
 * @param leftOperand
 * @param op
 * @param rightOperand
 * @return
 */
bool ConditionParser:: conditionRetVal (double leftOperand, double rightOperand, string op){
    //in case the operator is "<":
    if (op == "<"){
        return this->conditionSwitchCase(leftOperand, rightOperand, '<');
    }
    //in case the operator is ">":
    if (op == ">"){
        return this->conditionSwitchCase(leftOperand, rightOperand, '>');
    }
    //in case the operator is "==":
    if (op == "=="){
        return this->conditionSwitchCase(leftOperand, rightOperand, '=');
    }
    //in case the operator is ">=":
    if (op == ">="){
        return ((this->conditionSwitchCase(leftOperand, rightOperand, '=') ||
                (this->conditionSwitchCase(leftOperand, rightOperand, '>'));
    }
    //in case the operator is "<=":
    if (op == "<="){
        return ((this->conditionSwitchCase(leftOperand, rightOperand, '=') ||
                 (this->conditionSwitchCase(leftOperand, rightOperand, '<'));
    }
    //in case the operator is "!=":
    if (op == "!="){
        return !(this->conditionSwitchCase(leftOperand,rightOperand,'='));
    }

}