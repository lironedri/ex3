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
    fstream file;
    file.open (fileName, fstream::in | fstream::out | fstream::app);
    ifstream infile(fileName);
    string line;
    vector<vector<string>> allLines;
    while(getline(infile, line)) {
        if (line == "\n") {
            continue;
        }
        vector<string> lex = lineLexer(line);
        allLines.push_back(lex);
    }
    file.close();
    vector<string> data;
    for(int i = 0; i < allLines.size(); i++){
        for(int j = 0; j < allLines[i].size(); j++){
            data.push_back(allLines[i][j]);
        }
    }
    return data;
}

void cutSpaces(string* s){
    string exp, temp;
    istringstream line(*s);
    while(getline(line,temp,' ')){
        exp+=temp;
    }
    *s = exp;
}

bool isOperator(char c){
    return (c == '+' || c == '-' || c == '/' || c == '*');
}

bool isLetter(char c){
    return (isalpha(c));
}

vector<string> separateExpressions(string line){
    vector<string> expressions;
    string exp;
    char prev = 0;
    bool operatorShow = false;
    bool flagForNum = false;
    for(char c:line){
        if(isOperator(c)){
            exp+=c;
            operatorShow = true;
            flagForNum= false;
        } else if(isLetter(c)||c == '_'||isdigit(c)!=0||c=='.'){
            // if there is space and no operator before it's space between expressions.
            if(!exp.empty() && !operatorShow && prev==' '){
                expressions.push_back(exp);
                exp.clear();
                if(flagForNum)
                    flagForNum=false;
            }
            if(isdigit(c)!=0||c=='.'){
                if(prev==' '||operatorShow)
                    flagForNum = true;
            } else {
                //if var started with number- throw exception
                if(flagForNum){
                    __throw_invalid_argument("Invalid var format");
                }
            }
            exp += c;
            operatorShow = false;
        } else if(c == ' '||c=='('||c==')'){
            if(c!=' '){
                exp+=c;
            }
        } else {
            break;
        }
        prev=c;
    }
    if(!exp.empty()){
        expressions.push_back(exp);
    }
    return expressions;
}
vector<string> connectLexer(string s){
    //lexer for connect command
    vector<string> parsedLine;
    string connect = "connect";
    size_t isConnect = s.find(connect);
    parsedLine.push_back(connect);
    size_t startIP = isConnect+connect.length();
    s = s.substr(startIP);
    vector<string> vec = separateExpressions(s);
    if(vec.size()!=2){
        __throw_invalid_argument("Invalid arguments for connect command");
    }
    string legalFormat = "([0-9]+[.]){3}[0-9]+";
    regex legalIP(legalFormat);
    smatch IP;
    regex_match(vec[0], IP, legalIP);
    if(IP.empty()){
        __throw_invalid_argument("Invalid IP");
    }
    parsedLine.push_back(IP[0]);
    parsedLine.push_back(vec[1]);
    if(s.find('}')!= string::npos){
        parsedLine.push_back("}");
    }
    return parsedLine;
}
vector<string> sleepLexer(string s){
    //lexer for sleep command
    vector<string> parsedLine;
    parsedLine.push_back("sleep");
    size_t startIndex= s.find(' ');
    if(startIndex!=0){
        __throw_invalid_argument("Must have space after sleep command");
    }
    vector<string> args = separateExpressions(s);
    if(args.size()!=1){
        __throw_invalid_argument("Invalid parameters for sleep command");
    }
    parsedLine.push_back(args[0]);
    if(s.find('}')!= string::npos){
        parsedLine.push_back("}");
    }
    return parsedLine;
}
vector<string> printLexer(string s) {
    vector<string> parsedLine;
    string print = "print";
    parsedLine.push_back(print);
    size_t startPath = s.find('"');
    if (startPath != string::npos) {
        size_t endPath = s.find('"', startPath + 1);
        string checkIfVaild = s.substr(endPath + 1);
        cutSpaces(&checkIfVaild);
        if (endPath == string::npos || checkIfVaild.length()) {
            if(checkIfVaild!="}"||endPath == string::npos)
                __throw_invalid_argument("Invalid arguments for var command");
        }
        string msg = s.substr(startPath, endPath);
        parsedLine.push_back(msg);
    } else {
        // print expression
        size_t startIndex= s.find(print)+print.length();
        string msg = s.substr(startIndex);
        vector<string> vec = separateExpressions(msg);
        if(vec.size()!=1) {
            __throw_invalid_argument("Invalid arguments for print command");
        } else {
            parsedLine.push_back(msg);
        }
    }
    if(s.find('}')!= string::npos){
        parsedLine.push_back("}");
    }
    return parsedLine;
}
vector<string> assignLexer(string s){
    vector<string> parsedAssign;
    vector<string> split;
    istringstream line(s);
    string exp;
    vector<string> beforeAssignment = separateExpressions(s);
    for(string str: beforeAssignment){
        parsedAssign.push_back(str);
    }
    parsedAssign.push_back("=");
    vector<string> afterAssignment = separateExpressions(s.substr(s.find('=')+1));
    string checkIfValid;
    // bind with expression or bind to path
    if(afterAssignment[0] == "bind"){
        parsedAssign.push_back(afterAssignment[0]);
        // bind with path
        if(afterAssignment.size()==1) {
            size_t startPath = s.find('"')+1;
            if (startPath != string::npos) {
                size_t endPath = s.find('"', startPath );
                if (endPath == string::npos) {
                    __throw_invalid_argument("Invalid path to bind");
                }
                string path = s.substr(startPath-1, endPath - startPath+2);
                checkIfValid = s.substr(endPath + 1);
                cutSpaces(&checkIfValid);
                parsedAssign.push_back(path);

            }
        }else {
            // bind with var
            if (afterAssignment.size() != 2) {
                if (afterAssignment.size() == 3) {
                    checkIfValid = afterAssignment[2];
                    cutSpaces(&checkIfValid);
                } else {
                    __throw_invalid_argument("Invalid arguments for var command");
                }
            } else {
                parsedAssign.push_back(afterAssignment[1]);
            }
        }
    } else {
        if(afterAssignment.size()!=1){
            if(afterAssignment.size()==2){
                checkIfValid = afterAssignment[1];
                cutSpaces(&checkIfValid);
            } else {
                __throw_invalid_argument("Invalid arguments for var command");
            }
        } else {
            parsedAssign.push_back(afterAssignment[0]);
        }
    }
    if(!checkIfValid.empty()){
        if(checkIfValid != "}"){
            __throw_invalid_argument("Invalid arguments for var command");
        } else {
            parsedAssign.push_back(checkIfValid);
        }
    }
    return parsedAssign;
}
vector<string> openServerLexer(string s){
    vector<string> parsedLine;
    string openData = "openDataServer";
    parsedLine.push_back(openData);
    s = s.substr(openData.length());
    vector<string> params = separateExpressions(s);
    if(params.size()!=2){
        __throw_invalid_argument("Number of arguments doesn't fit to command");
    } else {
        string firstParam = params[0];
        cutSpaces(&firstParam);
        string secondParam = params[1];
        cutSpaces(&secondParam);
        parsedLine.push_back(firstParam);
        parsedLine.push_back(secondParam);
    }
    return parsedLine;
}
int isConditionalBlock(string s){
    size_t whileC = s.find("while");
    size_t ifC = s.find("if");
    if(whileC != string::npos){
        return 1;
    } else if(ifC != string::npos){
        return 2;
    } else {
        return 0;
    }
}
vector<string> Interpreter::lineLexer(string s){
    vector<string> parsedLine;
    size_t isAssign = s.find('=');
    size_t isPrint = s.find("print");
    size_t isSleep = s.find("sleep");
    size_t isOpenServer = s.find("openDataServer");
    size_t isConnect = s.find("connect");

    if(isPrint != string::npos){
        return printLexer(s);
    } else if(isSleep != string::npos){
        string sleep = "sleep";
        s = s.substr(isSleep+sleep.length());
        return sleepLexer(s);

    } else if(isConditionalBlock(s)){
        int condition = isConditionalBlock(s);
        size_t startIndex = 0;
        if(condition == 1){
            parsedLine.push_back("while");
            startIndex = s.find("while")+5;
        } else {
            parsedLine.push_back("if");
            startIndex = s.find("if")+2;
        }
        s = s.substr(startIndex+1);
        size_t bracketOpenIndex = s.find('(');
        int counter = 0;
        while(bracketOpenIndex!=string::npos){
            counter++;
            s.erase(bracketOpenIndex, 1);
            size_t bracketCloseIndex = s.find(')');
            if(bracketCloseIndex==string::npos){
                __throw_invalid_argument("Can't has only open bracket");
            } else {
                counter--;
                s.erase(bracketCloseIndex, 1);
                bracketOpenIndex = s.find('(');
            }
        }
        if(counter!=0){
            __throw_invalid_argument("open brackets not matched to closure");
        }
        if(s.find('{')!=string::npos){
            size_t x=s.find('{');
            s = s.substr(0,x);
            cutSpaces(&s);
            parsedLine.push_back(s);
            parsedLine.push_back("{");
        } else {
            cutSpaces(&s);
            parsedLine.push_back(s);
        }
        return parsedLine;
    }     else if(isAssign != string::npos){
        return assignLexer(s);
    } else if(isOpenServer != string::npos){
        return openServerLexer(s);
    } else if(isConnect != string::npos) {
        return connectLexer(s);
    } else{
        cutSpaces(&s);
        if(s=="}"||s=="{"){
            parsedLine.push_back(s);
            return parsedLine;
        }
    }
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



