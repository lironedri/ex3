#include "IfCommand.h"
#include <string.h>

int IfCommand::execute(vector<string> data, int index){
    int ifIndex = index + 3;
    doAllCommandsInScope(data, ifIndex);

    while ((strcmp(data[index].c_str(), "}")) != 0) {
        index++;
    }
    return (index + 1);
}