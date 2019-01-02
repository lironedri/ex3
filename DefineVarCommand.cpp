#include "DefineVarCommand.h"
#include "ShuntingYard.h"

int DefineVarCommand::execute(vector<string> data, int index) {
    // if the var isn't initialized yet (the vector contains "var, varName, =, bind, path").
    if (data[index] == "var") {
        if (data[index + 3] == "bind") {
            this->m_symbolTable->insertVarBind(data[index + 1], data[index + 4]);
            this->m_symbolTable->insertVarValue(data[index + 1], this->m_symbolTable->getVarValue(data[index + 4]));
            return 5;
            // in case a new var is initialized to the value of another var
            // (the vector contains "var, varName, =, varName2").
        } else {
            this->m_symbolTable->insertVarValue(data[index + 1], this->m_symbolTable->getVarValue(data[index + 3]));
            return 4;
        }
        /* in case the var is already initialized and we want to change its value
         (the vector contains "varName, =, value").*/
    } else {
        if (this->m_symbolTable->isVarBindExist(data[index])) {
            ShuntingYard *shuntingYard = new ShuntingYard(this->m_symbolTable);
            double value = shuntingYard->evaluate(data[index + 2])->calculate();
            this->m_symbolTable->insertVarValue(data[index], value);
            return 3;
        } else {
            throw "unknown command!";
            // todo - catch the exception
        }
    }
}