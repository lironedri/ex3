#include <iostream>
#include "PrintCommand.h"
#include "ShuntingYard.h"

int PrintCommand::execute(vector<string> data, int index){
    // in case we need to print string, the char " will be in the string
    if(data[index + 1].find("\"") != string::npos){
        cout << data[index + 1].substr(1, data[index + 1].length() - 2) << endl;
        // in case we need to print var
    } else{
        cout << this->m_dataBase.getVarValue(data[index + 1]) << endl;
    }
    return index + 2;
}