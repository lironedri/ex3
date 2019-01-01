#include "LoopCommand.h"
#include <string.h>

int LoopCommand::execute(vector<string> data, int index) {
    int loopIndex = index + 3;
    //todo doWhile? - make sure it's true.
    do {
        this->m_conditionParser->doAllCommandsInScope(data, loopIndex);

        this->m_conditionParser->m_leftOperand =
                this->m_conditionParser->calculateOperand(this->m_conditionParser->m_leftOperandStr);
        this->m_conditionParser->m_rightOperand =
                this->m_conditionParser->calculateOperand(this->m_conditionParser->m_rightOperandStr);
    } while (this->m_conditionParser->conditionRetVal(this->m_conditionParser->m_operandStr));

    while (data[loopIndex] != "}") {
        loopIndex++;
    }
    return (loopIndex - index + 1);
}