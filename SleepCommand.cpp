#include <unistd.h>
#include "SleepCommand.h"
#include "ShuntingYard.h"

int SleepCommand::execute(vector<string> data, int index){
    usleep((int)ShuntingYard(m_symbolTable).evaluate(data[index + 1])->calculate() * 1000);
    return 2;
}
