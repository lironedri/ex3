#include "OpenServerCommand.h"
#include "Expression.h"

/**
 * the function gets a string - the command, and a string vector data - the script from Lexer - and while the next
 * strings in the data vector is not any type of command - it
 * @param s
 * @param data
 * @return
 */
int OpenServerCommand::execute(vector<string> data, int index) {
    ShuntingYard* portExp = new ShuntingYard();
    Expression* port = portExp->evaluate(data[index + 1]);

}