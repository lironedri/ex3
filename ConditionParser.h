#ifndef EX3_CONDITIONPARSER_H
#define EX3_CONDITIONPARSER_H

#include <map>
#include "Command.h"

class ConditionParser : public Command {
    map<string, Command*> commandsMap;

public:
    int execute(vector<string> data, int index) = 0;
    virtual bool conditionSwitchCase(double leftOperand, double rightOperand, char op) = 0;
    virtual bool conditionRetVal (double leftOperand, double rightOperand, string op) = 0;


    };

#endif //EX3_CONDITIONPARSER_H
