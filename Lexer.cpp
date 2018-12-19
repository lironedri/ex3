#include "Lexer.h"
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <algorithm>

/**
 * the function gets script file and split the words into string vector.
 * @param fileName
 * @return
 */
vector<string> Lexer:: doLexer (string fileName){
    string word = "";
    vector<string> lineData;
    ifstream myFile(fileName);
    if (myFile.is_open()) {
        while (!myFile.eof()) {
            getline(myFile, word, ' ');
            if(word == "\n" || word == "") {
                continue;
            } else if(stringEndsWith(word, "\n")){
                word = word.substr(0, word.length() - 1);
                // if the word contains "\n"
            } else if(word.find("\n") != string::npos){
                string word2 = "";
                for(size_t i = 0; i < word.length(); i++){
                    if(word.at(i) == '\n'){
                        int z = word.length();
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


bool Lexer::stringEndsWith(const string &str, const string &toMatch)
{
    if(str.size() >= toMatch.size() &&
       str.compare(str.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
        return true;
    else
        return false;
}





