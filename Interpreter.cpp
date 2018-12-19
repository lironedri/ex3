#include "Interpreter.h"
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <algorithm>

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

/**
 * the function gets a string - str, and substring - toMach and return if the string end with the given substring
 * @param str
 * @param toMatch
 * @return
 */
bool Interpreter::stringEndsWith(const string &str, const string &toMatch)
{
    if(str.size() >= toMatch.size() &&
       str.compare(str.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
        return true;
    else
        return false;
}

/**
 * the function get
 * @param commandStr
 * @return
 */
Command Interpreter:: parser(vector<string> data){

}




