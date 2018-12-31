#ifndef EX3_VARCOMMAND_H
#define EX3_VARCOMMAND_H

#include "Command.h"

class DefineVarCommand : public Command {
    SymbolTable* m_symbolTable;

public:
    DefineVarCommand(SymbolTable* symbolTable){
        this->m_symbolTable = symbolTable;
    }
    virtual int execute(vector<string> data, int index);
};


#endif //EX3_VARCOMMAND_H
