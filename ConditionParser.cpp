#include "ConditionParser.h"
#include <string.h>
#include "LoopCommand.h"
#include "IfCommand.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "ShuntingYard.h"
#include <string>

int ConditionParser::execute(vector<string> data, int index) {
    string condition = data[index + 1];
    for(size_t i = 0; i < condition.length(); i++){
        if(condition[i] == '<' || condition[i] == '>'){
            if(condition[i + 1] == '='){
                this->m_leftOperandStr = condition.substr(0, i);
                this->m_operandStr = condition.substr(i, 2);
                this->m_rightOperandStr = condition.substr(i + 2, condition.length() - (i + 2));
                break;
            } else{
                this->m_leftOperandStr = condition.substr(0, i);
                this->m_operandStr = condition[i];
                this->m_rightOperandStr = condition.substr(i + 1, condition.length() - (i + 1));
                break;
            }
        } else if((condition[i] == '!' || condition[i] == '=') && condition[i + 1] == '='){
            this->m_leftOperandStr = condition.substr(0, i);
            this->m_operandStr = condition.substr(i, 2);
            this->m_rightOperandStr = condition.substr(i + 2, condition.length() - (i + 2));
            break;
        }
    }
    this->m_leftOperand = calculateOperand(this->m_leftOperandStr);
    this->m_rightOperand = calculateOperand(this->m_rightOperandStr);

    //check the condition
    //if the condition is true
    if (conditionRetVal(this->m_operandStr)) {
        Command *command;
        //if its a while loop
        if (data[index] == "while") {
            command = new LoopCommand(this->m_symbolTable);
            //if its a if command
        } else {
            command = new IfCommand(this->m_symbolTable);
        }
        //todo - check if there is not {
        return command->execute(data, index);
        //if the condition is false return the the index after the scope ends
    } else {
        // todo - check scope in scope, means two or more } (counter?)
        while ((strcmp(data[index].c_str(), "}")) != 0) {
            index++;
        }
        return (index + 1);
    }
}

double ConditionParser::calculateOperand(string operandExp) {
    //in case the operand is a known var from the map
    if (this->m_symbolTable->isVarValueExist(operandExp)) {
        return (this->m_symbolTable->getVarValue(operandExp));
        //in case the operand is a number (given as a string) and not a known var from the map
    } else {
        ShuntingYard* shuntingYard = new ShuntingYard(this->m_symbolTable);
        return shuntingYard->evaluate(operandExp)->calculate();
    }
}


/**
 * the function gets operator as a char, in case we can convert the operator to one char
 * and returns a boolean value of the expression answer.
 * @param leftOperand
 * @param op
 * @param rightOperand
 * @return
 */
bool ConditionParser::conditionSwitchCase(char op) {
    switch (op) {
        case '<':
            return this->m_leftOperand < this->m_rightOperand;
        case '>':
            return this->m_leftOperand > this->m_rightOperand;
        case '=':
            return this->m_leftOperand == this->m_rightOperand;
    }
}

/**
 * the gets a string operator and returns the bool value of the condition by using the switch-case by char function
 * @param leftOperand
 * @param op
 * @param rightOperand
 * @return
 */
bool ConditionParser::conditionRetVal(string op) {
    //in case the operator is "<":
    if (op == "<") {
        return this->conditionSwitchCase('<');
    }
    //in case the operator is ">":
    if (op == ">") {
        return this->conditionSwitchCase('>');
    }
    //in case the operator is "==":
    if (op == "==") {
        return this->conditionSwitchCase('=');
    }
    //in case the operator is ">=":
    if (op == ">=") {
        return ((this->conditionSwitchCase('=')) ||
                (this->conditionSwitchCase('>')));
    }
    //in case the operator is "<=":
    if (op == "<=") {
        return ((this->conditionSwitchCase('=')) ||
                (this->conditionSwitchCase('<')));
    }
    //in case the operator is "!=":
    if (op == "!=") {
        return !(this->conditionSwitchCase('='));
    }

}

/**
 * while the scope is not end yet - do all commands in the scope
 * @param data
 * @param index
 */
void ConditionParser::doAllCommandsInScope(vector<string> data, int index){
    while (data[index] != "}") {
        Command *command;
        //in case the current string is a command
        if (data[index] == "openDataServer") {
            command = new OpenServerCommand(this->m_symbolTable);
        } else if (data[index] == "connect") {
            command = new ConnectCommand(this->m_symbolTable);
        } else if (data[index] == "var") {
            command = new DefineVarCommand(this->m_symbolTable);
        } else if (data[index] == "while" || data[index] == "if") {
            command = new ConditionParser(this->m_symbolTable);
        } else if (data[index] == "print") {
            command = new PrintCommand(this->m_symbolTable);
        } else if (data[index] == "sleep") {
            command = new SleepCommand(this->m_symbolTable);
            // in case the current string might be a var
        } else {
            command = new DefineVarCommand(this->m_symbolTable);
        }
        index += command->execute(data, index);
    }
}