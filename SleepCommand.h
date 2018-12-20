#ifndef EX3_SLEEPCOMMAND_H
#define EX3_SLEEPCOMMAND_H


#include "Command.h"

class SleepCommand : public Command{

public:
    virtual int execute(vector<string> data, int index);
};


#endif //EX3_SLEEPCOMMAND_H
