#include "IfCommand.h"
#include <string.h>

int IfCommand::execute(vector<string> data, int index){
    int ifIndex = index + 3;
    doAllCommandsInScope(data, ifIndex);

    //check which index the scope ends
    while (data[ifIndex] != "}") {
        ifIndex++;
    }
    return (ifIndex - index + 1);
}