#ifndef EX3_COMMANDEXPRESSION_H
#define EX3_COMMANDEXPRESSION_H

#include "Expression.h"
#include "Command.h"

class CommandExpression : public Expression{
    Command* m_command;
    vector<string> m_data;
    int m_index;

public:
    CommandExpression(Command* command, vector<string> data, int index){
        m_command = command;
        m_data = data;
        m_index = index;
    }

    virtual double calculate();
};


#endif //EX3_COMMANDEXPRESSION_H
