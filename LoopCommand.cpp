#include "LoopCommand.h"
#include <string.h>

int LoopCommand::execute(vector<string> data, int index) {
    while (conditionRetVal(this->m_operandStr)){

        int LoopIndex = index + 3;
        doAllCommandsInScope(data, LoopIndex);

        this->m_leftOperand = calculateOperand(this->m_leftOperandStr);
        this->m_rightOperand = calculateOperand(this->m_rightOperandStr);
    }

    while ((strcmp(data[index].c_str(), "}")) != 0) {
        index++;
    }
    return (index + 1);
}
