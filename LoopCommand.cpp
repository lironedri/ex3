#include "LoopCommand.h"
#include <string.h>

int LoopCommand::execute(vector<string> data, int index) {
    while (conditionRetVal(data[index + 2])) {

        int LoopIndex = index + 5;
        doAllCommandsInScope(data, LoopIndex);

        this->m_leftOperand = calculateOperand(data[index + 1]);
        this->m_rightOperand = calculateOperand(data[index + 3]);
    }

    while ((strcmp(data[index].c_str(), "}")) != 0) {
        index++;
    }
    return (index + 1);
}
