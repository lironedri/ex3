#ifndef EX3_IFCOMMAND_H
#define EX3_IFCOMMAND_H

#include "ConditionParser.h"
#include "Command.h"

class IfCommand : public Command{
    ConditionParser* m_conditionParser;

public:
    IfCommand(ConditionParser* conditionParser){
        this->m_conditionParser = conditionParser;
    }
    virtual int execute(vector<string> data, int index);

};


#endif //EX3_IFCOMMAND_H