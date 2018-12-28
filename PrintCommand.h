#ifndef EX3_PRINTCOMMAND_H
#define EX3_PRINTCOMMAND_H

#include "Command.h"

class PrintCommand : public Command{
public:
    virtual int execute(vector<string> data, int index);
};

#endif //EX3_PRINTCOMMAND_H
