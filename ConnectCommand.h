#ifndef EX3_CONNECTCOMMAND_H
#define EX3_CONNECTCOMMAND_H

#include "Command.h"

class ConnectCommand : public Command {

public:
    virtual int execute(vector<string> data, int index);
};


#endif //EX3_CONNECTCOMMAND_H
