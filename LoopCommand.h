#ifndef EX3_LOOPCOMMAND_H
#define EX3_LOOPCOMMAND_H

#include "ConditionParser.h"

class LoopCommand : public ConditionParser{

public:
    LoopCommand(SymbolTable* symbolTable){
        this->m_symbolTable = symbolTable;
    }
    virtual int execute(vector<string> data, int index);
};


#endif //EX3_LOOPCOMMAND_H
