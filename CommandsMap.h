#ifndef EX3_COMMANDSMAP_H
#define EX3_COMMANDSMAP_H

#include <map>
#include "Expression.h"
#include "OpenServerCommand.h"

using namespace std;

class CommandsMap{
    map<string, Expression*> m_commandsMap;

public:
    //todo define
    CommandsMap(){
        m_commandsMap["openDataServer"] =
    }
};

#endif //EX3_COMMANDSMAP_H
