#ifndef EX3_PRINTCOMMAND_H
#define EX3_PRINTCOMMAND_H

#include "Command.h"

class PrintCommand : public Command{
    SymbolTable* m_symbolTable;

public:
    PrintCommand(SymbolTable* symbolTable){
        this->m_symbolTable = symbolTable;
    }
    virtual int execute(vector<string> data, int index);
};

#endif //EX3_PRINTCOMMAND_H
