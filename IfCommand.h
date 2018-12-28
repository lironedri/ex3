#ifndef EX3_IFCOMMAND_H
#define EX3_IFCOMMAND_H

#include "ConditionParser.h"

class IfCommand : public ConditionParser{
     int execute(vector<string> data, int index) = 0;

};


#endif //EX3_IFCOMMAND_H
