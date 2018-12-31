#include "LoopCommand.h"
#include <string.h>

int LoopCommand::execute(vector<string> data, int index) {
    int loopIndex;
    while (conditionRetVal(this->m_operandStr)){

        loopIndex = index + 3;
        doAllCommandsInScope(data, loopIndex);

        this->m_leftOperand = calculateOperand(this->m_leftOperandStr);
        this->m_rightOperand = calculateOperand(this->m_rightOperandStr);
    }

    while (data[loopIndex] != "}") {
        loopIndex++;
    }
    return (loopIndex - index + 1);
}
