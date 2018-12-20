#ifndef EX3_CONDITIONPARSER_H
#define EX3_CONDITIONPARSER_H

#include <map>
#include "Command.h"

class ConditionParser : public Command {
    map<string, Command> commandsMap;

public:
    virtual int execute(vector<string> data, int index);
};


#endif //EX3_CONDITIONPARSER_H
