#ifndef EX3_IFCOMMAND_H
#define EX3_IFCOMMAND_H

#include "ConditionParser.h"

class IfCommand : public ConditionParser{

public:
     virtual int execute(vector<string> data, int index);

};


#endif //EX3_IFCOMMAND_H
