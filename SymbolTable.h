#ifndef EX3_DATABASE_H
#define EX3_DATABASE_H

#include <map>

using namespace std;

class SymbolTable {
    map<string, string> m_varBinds;
    map<string, double> m_varValues;

public:
    SymbolTable();
    map<string, string> getVarBindsMap();
    map<string, double> getVarValuesMap();
    void insertVarBind(string varKey, string pathValue);
    void insertVarValue(string varKey, double value);
    string getVarBind(string varKey);
    double getVarValue(string varKey);
    bool isVarValueExist(string varKey);
};


#endif //EX3_DATABASE_H
