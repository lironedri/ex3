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

using namespace std;

/**
 * the function gets script file and split the words into string vector.
 * @param fileName
 * @return
 */
vector<string> Interpreter:: lexer (string fileName){
//    string word = "";
//    vector<string> lineData;
//    ifstream myFile(fileName);
//    if (myFile.is_open()) {
//        while (!myFile.eof()) {
//            getline(myFile, word, ' ');
//            if(word == "\n" || word == "") {
//                continue;
//                //check if the word ends with "\n"
//            } else if(stringEndsWith(word, "\n")){
//                word = word.substr(0, word.length() - 1);
//                // if the word contains "\n"
//            } else if(word.find("\n") != string::npos){
//                string word2 = "";
//                //split the word that contains "\n" into two words without "\n"
//                for(size_t i = 0; i < word.length(); i++){
//                    if(word.at(i) == '\n'){
//                        word2 = word.substr(i + 1, word.length()-i-1);
//                        word = word.substr(0, i-1);
//                        lineData.push_back(word);
//                        lineData.push_back(word2);
//                        break;
//                    }
//                }
//            }
//            lineData.push_back(word);
//        }
//        myFile.close();
//    }
//    return lineData;
    list<string> oper = {"(", ")", "=", "+", "*", ",", "-", "/", "<", ">", "&", "|", "!","}","{"};
    list<string> output;
    list<string> output2;
    list<string> output3;
    smatch m;
    smatch m2;
    string s;

    regex r("\\S+");
    ifstream myfile(fileName);
    if (myfile.is_open()) {
        while (getline(myfile, s)) {
            // Search again and again
            while (regex_search(s, m, r)) {
                string s2 = m[0];
                output.push_back(s2);

                // remove everything until after this match, and search again
                s = m.suffix().str();
            }// next match

            for (list<string>::iterator op = oper.begin(); op != oper.end(); ++op) {
                for (list<string>::iterator it = output.begin(); it != output.end(); ++it) {

                    if (!(regex_match((*it), regex("^.[" + (*op) + "].$"))) ||
                        (regex_match((*it), regex("^\".\"$")))) {
                        output2.push_back((*it));
                        continue;
                    }
                    string s2 = (*it);
                    while (regex_search(s2, m, regex("[" + (*op) + "]")) &&
                    !(regex_match(s2, regex("^\".*\"$")))) {

                        if ((s2.substr(0, m.position(0))).compare("")) {
                            output2.push_back(s2.substr(0, m.position(0)));
                        }
                        output2.push_back((*op));
                        s2 = m.suffix().str();
                    }
                    if (s2.compare("")) {
                        output2.push_back(s2);
                    }
                }
                output.clear();
                ++op;
                if (op != oper.end()) {
                    for (list<string>::iterator it = output2.begin(); it != output2.end(); ++it) {
                        if (!(regex_match((*it), regex("^.[" + (*op) + "].$"))) ||
                            (regex_match((*it), regex("^\".\"$")))) {
                            output.push_back((*it));
                            continue;
                        }
                        string s2 = (*it);
                        while (regex_search(s2, m, regex("[" + (*op) + "]")) &&
                        !(regex_match(s2, regex("^\".*\"$")))) {

                            if ((s2.substr(0, m.position(0))).compare("")) {
                                output.push_back(s2.substr(0, m.position(0)));
                            }
                            output.push_back((*op));
                            s2 = m.suffix().str();
                        }
                        if (s2.compare("")) {
                            output.push_back(s2);
                        }
                    }
                    output2.clear();
                } else {
                    for (list<string>::iterator it = output2.begin(); it != output2.end(); ++it) {
                        output3.push_back((*it));
                    }

                    output2.clear();

                    break;

                }
            }

            for (list<string>::iterator it = output.begin(); it != output.end(); ++it) {
                output3.push_back((*it));
            }
            output.clear();

        }

    }
    myfile.close();
    vector<string> out;
    for (list<string>::iterator it = output3.begin(); it != output3.end(); ++it) {
        out.push_back((*it));
    }
    return out;
}

/**
 * the function gets a string - str, and substring - toMach and return if the string end with the given substring
 * @param str
 * @param toMatch
 * @return
 */
bool Interpreter::stringEndsWith(const string &str, const string &toMatch)
{
    return (str.size() >= toMatch.size() &&
        str.compare(str.size() - toMatch.size(), toMatch.size(), toMatch) == 0);

}

bool Interpreter::stringStartsWith(const string haystack, const string& needle) {
    return needle.length() <= haystack.length()
           && equal(needle.begin(), needle.end(), haystack.begin());
}

map<string, Expression*> Interpreter::createCommandsMap(vector<string> dataVec, int index){
    map<string, Expression*> commandsMap;
    //todo define
    commandsMap["openDataServer"] = new CommandExpression(new OpenServerCommand(), dataVec, index);
    commandsMap["connect"] = new CommandExpression(new ConnectCommand(), dataVec, index);
    commandsMap["var"] = new CommandExpression(new DefineVarCommand(), dataVec, index);
//    commandsMap["while"] = new CommandExpression(new ConditionParser(), dataVec, index);
//    commandsMap["if"] = new CommandExpression(new ConditionParser(), dataVec, index);
    commandsMap["print"] = new CommandExpression(new PrintCommand(), dataVec, index);
    commandsMap["sleep"] = new CommandExpression(new SleepCommand(), dataVec, index);

    return commandsMap;
}

/**
 * the function get
 * @param commandStr
 * @return
 */
void Interpreter:: parser(vector<string> dataVec){
    int index = 0;
    map<string, Expression*> commandsMap = createCommandsMap(dataVec, index);
    while(index <= dataVec.size()){
        //if the word is a command that exist in the map
        if(commandsMap.count(dataVec[index]) != 0){
            Expression* commandExp = commandsMap[dataVec[index]];
            index += (int)commandExp->calculate();
            // in case the current string is a var name and not command
        } else{
            Expression* commandExp = commandsMap.find("var")->second;
            index += (int)commandExp->calculate();
        }
    }
}



