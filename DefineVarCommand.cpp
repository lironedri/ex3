#include "DefineVarCommand.h"

int DefineVarCommand::execute(vector<string> data, int index){
    // if the var isn't initialized yet (the vector contains "var, varName, =, bind, path").
    if(data[0] == "var"){
        this->m_dataBase->insertVarBind(data[index + 1], data[index + 4]);
        return index + 5;
        /* in case the var is already initialized and we want to change its value
         (the vector contains "varName, =, value").*/
    } else{
        if(this->m_dataBase->isVarValueExist(data[index])){
            string::size_type sz;
            this->m_dataBase->insertVarValue(data[index], stod(data[index + 2], &sz));
            return index + 3;
        } else{
            throw "unknown command!";
            // todo - catch the exception
        }
    }
}