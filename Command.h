//
// Created by liron on 12/19/18.
//

#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H
#include <string>
#include <vector>

using namespace std;

class Command {
public:
    virtual int execute(string s, vector<string>* data);
};

#endif //EX3_COMMAND_H
