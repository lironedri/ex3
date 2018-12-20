#include "OpenServerCommand.h"
#include "Expression.h"
#include "Plus.h"

/**
 * the function gets a string - the command, and a string vector data - the script from Lexer - and while the next
 * strings in the data vector is not any type of command - it
 * @param s
 * @param data
 * @return
 */
int OpenServerCommand::execute(vector<string> data, int index) {
    Expression* port;
//    port = data[index + 1];
}