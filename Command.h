#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H
#include <string>
#include <vector>
#include "Expression.h"
#include "ShuntingYard.h"

using namespace std;

class Command {

public:
    virtual int execute(vector<string> data, int index);
};

#endif //EX3_COMMAND_H
