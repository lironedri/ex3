#ifndef EX3_OPENSERVERCOMMAND_H
#define EX3_OPENSERVERCOMMAND_H
#include "Command.h"

class OpenServerCommand : public Command{
public:
    virtual int execute(vector<string> data, int index);
};


#endif //EX3_OPENSERVERCOMMAND_H
