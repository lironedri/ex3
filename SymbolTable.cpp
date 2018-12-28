#include "SymbolTable.h"

SymbolTable::SymbolTable(){

}

map<string, string> SymbolTable::getVarBindsMap(){
    return this->m_varBinds;
}

map<string, double> SymbolTable::getVarValuesMap(){
    return this->m_varValues;
}

void SymbolTable::insertVarBind(string varKey, string pathValue){
    this->m_varBinds[varKey] = pathValue;
}

void SymbolTable::insertVarValue(string varKey, double value){
    this->m_varValues[varKey] = value;
}

string SymbolTable::getVarBind(string varKey){
    return this->m_varBinds.find(varKey)->second;
}

double SymbolTable::getVarValue(string varKey){
    return this->m_varValues.find(varKey)->second;
}

bool SymbolTable::isVarValueExist(string varKey){
    return this->m_varValues.count(varKey) > 0;
}

