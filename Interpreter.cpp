#include "Interpreter.h"
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <list>
#include <regex>
#include "Expression.h"
#include "CommandExpression.h"
#include "ConnectCommand.h"
#include "PrintCommand.h"
#include "OpenServerCommand.h"
#include "SleepCommand.h"
#include "DefineVarCommand.h"
#include "ConditionParser.h"

using namespace std;

/**
 * the function gets script file and split the words into string vector.
 * @param fileName
 * @return
 */
vector<string> Interpreter:: lexer (string fileName){
    string word = "";
    vector<string> lineData;
    ifstream myFile(fileName);
    if (myFile.is_open()) {
        while (!myFile.eof()) {
            getline(myFile, word, ' ');
            if(word == "\n" || word == "") {
                continue;
                //check if the word ends with "\n"
            } else if(stringEndsWith(word, "\n")){
                word = word.substr(0, word.length() - 1);
                // if the word contains "\n"
            } else if(word.find("\n") != string::npos){
                string word2 = "";
                //split the word that contains "\n" into two words without "\n"
                for(size_t i = 0; i < word.length(); i++){
                    if(word.at(i) == '\n'){
                        word2 = word.substr(i + 1, word.length()-i-1);
                        word = word.substr(0, i-1);
                        lineData.push_back(word);
                        lineData.push_back(word2);
                        break;
                    }
                }
            }
            lineData.push_back(word);
        }
        myFile.close();
    }
    return lineData;
}

/**
 * the function gets a string - str, and substring - toMach and return if the string end with the given substring
 * @param str
 * @param toMatch
 * @return
 */
bool Interpreter::stringEndsWith(const string &str, const string &toMatch){
    return (str.size() >= toMatch.size() &&
        str.compare(str.size() - toMatch.size(), toMatch.size(), toMatch) == 0);

}

bool Interpreter::stringStartsWith(const string haystack, const string& needle){
    return needle.length() <= haystack.length()
           && equal(needle.begin(), needle.end(), haystack.begin());
}

/**
 * the function get
 * @param commandStr
 * @return
 */
void Interpreter:: parser(vector<string> dataVec){
    int index = 0;
    Expression* commandExp;
    while(index <= dataVec.size()){
        //if the current string is a command
        if(dataVec[index] == "openDataServer"){
            commandExp = new CommandExpression(new OpenServerCommand(), dataVec, index);
        } else if(dataVec[index] == "connect"){
            commandExp = new CommandExpression(new ConnectCommand(), dataVec, index);
        } else if(dataVec[index] == "var"){
            commandExp = new CommandExpression(new DefineVarCommand(), dataVec, index);
        } else if(dataVec[index] == "while" || dataVec[index] == "if"){
            commandExp = new CommandExpression(new ConditionParser(), dataVec, index);
        } else if(dataVec[index] == "print"){
            commandExp = new CommandExpression(new PrintCommand(), dataVec, index);
        } else if(dataVec[index] == "sleep"){
            commandExp = new CommandExpression(new SleepCommand(), dataVec, index);
            // in case the current string is not a command
        } else{
            throw "unknown command";
        }
        index += (int)commandExp->calculate();
    }
}



