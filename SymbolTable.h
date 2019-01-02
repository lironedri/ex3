#ifndef EX3_SYMBOLTABLE_H
#define EX3_SYMBOLTABLE_H

#include <map>
#include "SocketWriteRead.h"

using namespace std;

#define PATHS_AMOUNT 23

class SymbolTable {
    map<string, string> m_varBinds;
    map<string, double> m_varValues;
    map<string, int> m_pathToIndex;
    double m_pathsValue[PATHS_AMOUNT];
    int m_clientSocket;
    SocketWriteRead socketWriteRead;

    void insertPathValue(string pathKey, double value, bool updateSimulator,bool updateBind);
    void insertVarValue(string varKey, double value,bool updateBind);
    void updateSimulator(string path, double value);
    void updateBindVars(string var, double value);
public:
    SymbolTable();
    map<string, string> getVarBindsMap();
    map<string, double> getVarValuesMap();
    void insertVarBind(string varKey, string pathValue);
    void insertVarValue(string varKey, double value);
    void insertPathValue(string pathKey, double value);
    void insertPathValue(int pathIndex, double value);
    string getVarBind(string varKey);
    double getVarValue(string varKey);
    bool isVarValueExist(string varKey);
    bool isPathValueExist(string pathKey);
    bool isVarBindExist(string varKey);
    void setClientSocket(int socket);
};


#endif //EX3_SYMBOLTABLE_H
