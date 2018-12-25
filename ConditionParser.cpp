#include "ConditionParser.h"

int ConditionParser::execute(vector<string> data, int index) {
    double firstOperand, secondOperand;
    if(this->m_dataBase.isVarValueExist(data[index + 1])){
        firstOperand = this->m_dataBase.getVarValue(data[index + 1]);
        //convert the data[index + 1] from string to double
    } else {

    }

    //second operand todo - change to second
    if(this->m_dataBase.isVarValueExist(data[index + 1])){
        firstOperand = this->m_dataBase.getVarValue(data[index + 1]);
        //convert the data[index + 1] from string to double
    } else {

    }
}
