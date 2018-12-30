#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H

#include <string>
#include <vector>
#include "SymbolTable.h"

using namespace std;

class Command {
protected:
    SymbolTable* m_dataBase;

public:
    Command(){

    }

    virtual int execute(vector<string> data, int index) = 0;
};

#endif //EX3_COMMAND_H
