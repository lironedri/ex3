#include "SymbolTable.h"

SymbolTable::SymbolTable() {
    this->m_clientSocket = -1;
    this->m_pathToIndex = {
            {"/instrumentation/airspeed-indicator/indicated-speed-kt",        0},
            {"/instrumentation/altimeter/indicated-altitude-ft",              1},
            {"/instrumentation/altimeter/pressure-alt-ft",                    2},
            {"/instrumentation/attitude-indicator/indicated-pitch-deg",       3},
            {"/instrumentation/attitude-indicator/indicated-roll-deg",        4},
            {"/instrumentation/attitude-indicator/internal-pitch-deg",        5},
            {"/instrumentation/attitude-indicator/internal-roll-deg",         6},
            {"/instrumentation/encoder/indicated-altitude-ft",                7},
            {"/instrumentation/encoder/pressure-alt-ft",                      8},
            {"/instrumentation/gps/indicated-altitude-ft",                    9},
            {"/instrumentation/gps/indicated-ground-speed-kt",                10},
            {"/instrumentation/gps/indicated-vertical-speed",                 11},
            {"/instrumentation/heading-indicator/indicated-heading-deg",      12},
            {"/instrumentation/magnetic-compass/indicated-heading-deg",       13},
            {"/instrumentation/slip-skid-ball/indicated-slip-skid",           14},
            {"/instrumentation/turn-indicator/indicated-turn-rate",           15},
            {"/instrumentation/vertical-speed-indicator/indicated-speed-fpm", 16},
            {"/controls/flight/aileron",                                      17},
            {"/controls/flight/elevator",                                     18},
            {"/controls/flight/rudder",                                       19},
            {"/controls/flight/flaps",                                        20},
            {"/controls/engines/engine/throttle",                             21},
            {"/engines/engine/rpm",                                           22}
    };
}

map<string, string> SymbolTable::getVarBindsMap() {
    return this->m_varBinds;
}

map<string, double> SymbolTable::getVarValuesMap() {
    return this->m_varValues;
}

void SymbolTable::insertVarBind(string varKey, string pathValue) {
    if (pathValue[0] == '\"') {
        pathValue = pathValue.substr(1, pathValue.length() - 2);
    }

    this->m_varBinds[varKey] = pathValue;
}

void SymbolTable::insertVarValue(string varKey, double value) {
    insertVarValue(varKey, value, true);
}

string SymbolTable::getVarBind(string varKey) {
    return this->m_varBinds.find(varKey)->second;
}

double SymbolTable::getVarValue(string varKey) {
    if (varKey[0] == '\"') {
        varKey = varKey.substr(0, varKey.length() - 2);
    }

    if (isPathValueExist(varKey)) {
        return this->m_pathsValue[m_pathToIndex[varKey]];
    }

    if (isVarValueExist(varKey)) {
        return this->m_varValues.find(varKey)->second;
    }

    return 0;
}

bool SymbolTable::isVarValueExist(string varKey) {
    return this->m_varValues.count(varKey) > 0;
}

bool SymbolTable::isPathValueExist(string pathKey) {
    return this->m_pathToIndex.count(pathKey) > 0;
}

bool SymbolTable::isVarBindExist(string varKey) {
    return this->m_varBinds.count(varKey) > 0;
}

void SymbolTable::insertPathValue(string pathKey, double value, bool updateSimulator, bool updateBind) {
    if (!isPathValueExist(pathKey)) {
        return;
    }

    this->m_pathsValue[this->m_pathToIndex[pathKey]] = value;

    if (updateBind) {
        updateBindVars(pathKey, value);
    }

    if (updateSimulator && this->m_clientSocket > 0) {
        socketWriteRead.socketWrite(m_clientSocket, "set " + pathKey.substr(1) + " " + to_string(value) + " \r\n");
    }
}

void SymbolTable::insertPathValue(int pathIndex, double value) {
    if (pathIndex >= 0 && pathIndex < PATHS_AMOUNT) {
        for (auto &it : this->m_pathToIndex) {
            if (it.second == pathIndex) {
                this->insertPathValue(it.first, value, false, true);
            }
        }
    }
}

void SymbolTable::setClientSocket(int socket) {
    this->m_clientSocket = socket;
}

void SymbolTable::insertPathValue(string pathKey, double value) {
    insertPathValue(pathKey, value, true, true);
}

void SymbolTable::updateBindVars(string var, double value) {
    for (auto &it : this->m_varBinds) {
        string updateVar;
        if (it.first == var) {
            updateVar = it.second;
        }
        if (it.second == var) {
            updateVar = it.first;
        }

        if (!updateVar.empty()) {
            insertPathValue(updateVar, value, true, false);
            insertVarValue(updateVar, value, false);
        }
    }
}

void SymbolTable::insertVarValue(string varKey, double value, bool updateBind) {
    this->m_varValues[varKey] = value;

    if (updateBind) {
        updateBindVars(varKey, value);
    }
}
