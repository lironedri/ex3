#ifndef EX3_LOOPCOMMAND_H
#define EX3_LOOPCOMMAND_H

#include "ConditionParser.h"
#include "Command.h"

class LoopCommand : public Command{
    ConditionParser* m_conditionParser;

public:
    LoopCommand(ConditionParser* conditionParser){
        this->m_conditionParser = conditionParser;
    }
    virtual int execute(vector<string> data, int index);
};


#endif //EX3_LOOPCOMMAND_H