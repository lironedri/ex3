#ifndef EX3_SLEEPCOMMAND_H
#define EX3_SLEEPCOMMAND_H


#include "Command.h"

class SleepCommand : public Command{
    SymbolTable* m_symbolTable;

public:
    SleepCommand(SymbolTable* symbolTable){
        this->m_symbolTable = symbolTable;
    }
    virtual int execute(vector<string> data, int index);
};


#endif //EX3_SLEEPCOMMAND_H