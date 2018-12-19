#ifndef EX3_OPENSERVERCOMMAND_H
#define EX3_OPENSERVERCOMMAND_H
#include "Command.h"

class OpenServerCommand : public Command{
public:
    int execute(string s, vector<string>* data);
};


#endif //EX3_OPENSERVERCOMMAND_H
