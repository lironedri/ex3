#ifndef EX3_CONDITIONPARSER_H
#define EX3_CONDITIONPARSER_H

#include "Command.h"
#include "Expression.h"

class ConditionParser : public Command {
protected:
    SymbolTable* m_symbolTable;
protected:
    map<string, Expression*> commandsMap;
    double m_leftOperand;
    double m_rightOperand;
    string m_leftOperandStr;
    string m_rightOperandStr;
    string m_operandStr;

public:
    ConditionParser(SymbolTable* symbolTable){
        this->m_leftOperand = 0;
        this->m_rightOperand = 0;
        this->m_symbolTable = symbolTable;
    }

    ConditionParser(){};

    virtual int execute(vector<string> data, int index);
    bool conditionSwitchCase(char op);
    bool conditionRetVal(string op);
    double calculateOperand(string operandExp);
    void doAllCommandsInScope(vector<string> data, int index);
};

#endif //EX3_CONDITIONPARSER_H
