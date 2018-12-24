#ifndef EX3_CONDITIONPARSER_H
#define EX3_CONDITIONPARSER_H

#include <map>
#include "Command.h"

class ConditionParser : public Command {
    map<string, Command*> commandsMap;

public:
    int execute(vector<string> data, int index) override;
};

#endif //EX3_CONDITIONPARSER_H
