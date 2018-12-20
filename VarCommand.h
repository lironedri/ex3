#ifndef EX3_VARCOMMAND_H
#define EX3_VARCOMMAND_H

#include "Command.h"

class VarCommand : public Command {

public:
    virtual int execute(vector<string> data, int index);
};


#endif //EX3_VARCOMMAND_H
