#include "ConditionParser.h"
#include <string.h>
#include "LoopCommand.h"
#include "IfCommand.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"

int ConditionParser::execute(vector<string> data, int index) {
    this->m_leftOperand = calculateOperand(data[index + 1]);
    this->m_rightOperand = calculateOperand(data[index + 3]);

    //check the condition
    //if the condition is true
    if (conditionRetVal(data[index + 2])) {
        Command *command;
        //if its a while loop
        if (data[index] == "while") {
            command = new LoopCommand();
            //if its a if command
        } else {
            command = new IfCommand();
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
    if (this->m_dataBase.isVarValueExist(operandExp)) {
        return (this->m_dataBase.getVarValue(operandExp));
        //in case the operand is a number (given as a string) and not a known var from the map
    } else {
        string::size_type sz;
        return (stod(operandExp, &sz));
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

void ConditionParser::doAllCommandsInScope(vector<string> data, int index){
    while ((strcmp(data[index].c_str(), "}")) != 0) {
        Command *command;
        //in case the current string is a command
        if (data[index] == "openDataServer") {
            command = new OpenServerCommand();
        } else if (data[index] == "connect") {
            command = new ConnectCommand();
        } else if (data[index] == "var") {
            command = new DefineVarCommand();
        } else if (data[index] == "while" || data[index] == "if") {
            command = new ConditionParser();
        } else if (data[index] == "print") {
            command = new PrintCommand();
        } else if (data[index] == "sleep") {
            command = new SleepCommand();
            // in case the current string might be a var
        } else {
            command = new DefineVarCommand();
        }
        index += command->execute(data, index);
    }
}