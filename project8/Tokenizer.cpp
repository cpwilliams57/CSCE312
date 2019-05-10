//
//  Tokenizer.cpp
//  Project8
//
//  Created by Kaleb Lewis on 11/27/17.
//  Copyright © 2017 Kaleb Lewis. All rights reserved.
//

#include "Tokenizer.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <queue>

tokenizer::tokenizer(string fileInput) {
    string temp = fileInput;
    fileName = temp.substr(0, temp.length() - 5) + "Token.xml";
    
    readTokens(fileInput);
};


void tokenizer::readTokens(string fileIn) {
    bool blockComment = false;
    fstream file(fileIn);
    
    string fileLine;
    
    while (file.good()) {
        getline(file, fileLine, '\n');
        fileLine = scanLine(fileLine, blockComment);
        
        makeTokens(fileLine);
    }
};

void tokenizer::makeTokens(string line) {
    queue<char> parseQueue;
    char curr;
    Token temp;
    string special;
    bool activeStr = false;
    for (int i = 0; i < line.length() ; i++) {
        curr = line[i];
        if (curr == '"') {
            activeStr = !activeStr;
        }
        if ((!isSymbol(curr) && (!isspace(curr))) || activeStr) {
            
            parseQueue.push(curr);
        }
        else if (!activeStr) {
            if (!parseQueue.empty()) {
                temp = idToken(parseQueue);
                tokens.push_back(temp);
            }
            
            if (!isspace(curr)) {
                if (isSpecial(curr)) {
                    special = equalSet[curr];
                    temp = Token(special, "symbol");
                    tokens.push_back(temp);
                }
                else {
                    temp = Token(curr, "symbol");
                    tokens.push_back(temp);
                }
            }
            
        }
    }
};

Token tokenizer::idToken(queue<char> &parseQueue) {
    string stackStr;
    Token stackToken;
    while (!parseQueue.empty()) {
        //stackStr.push_front(parseQueue.top());
        //stackStr.insert(stackStr.begin(), parseQueue.enqueue());
        
        stackStr += parseQueue.front();
        parseQueue.pop();
    }
    
    //Checking for keyword
    if (isKeyword(stackStr)) {
        
        stackToken = Token(stackStr, "keyword");
        return stackToken;
    }
    //Checking for string
    else if ((stackStr[0] == '"') && (stackStr[stackStr.length()-1] == '"')) {
        stackStr = stackStr.substr(1, stackStr.length() - 2);
        stackToken = Token(stackStr, "stringConstant");
        return stackToken;
    }
    //Checking for int
    else if (isInt(stackStr)) {
        stackToken = Token(stackStr, "integerConstant");
        return stackToken;
    }
    //It's an identifier
    else {
        stackToken = Token(stackStr, "identifier");
        return stackToken;
    }
    
    
    return stackToken;
};

bool tokenizer::isSymbol(char input) {
    return (symbolSet.find(input) != symbolSet.end());
};

bool tokenizer::isSpecial(char input) {
    return (equalSet.find(input) != equalSet.end());
};

bool tokenizer::isKeyword(string input) {
    return (keySet.find(input) != keySet.end());
};

bool tokenizer::isInt(string input) {
    bool label = (input.find_first_not_of("1234567890") == string::npos);
    return label;
};

string tokenizer::scanLine(string line, bool &comment) {
    string scannedLine;
    char curr, next = '\0';
    
    line = line.substr(0, line.length());
    
    for (int i = 0 ; i < line.length() ; i++) {
        curr = line[i];
        
        if (i <= (line.length())) {
            next = line[i + 1];
        }
        
        if ((curr == '/') && (next == '*')) {
            comment = true;
        }
        else if ((curr == '/') && (next == '/')) {
            return scannedLine;
        }
        else if (!comment){
            scannedLine += curr;
        }
        else if ((curr == '*') && (next == '/')) {
            comment = false;
            i++;
        }
    }
    return scannedLine;
};

void tokenizer::printTokens() {
    for (int i = 0 ; i < tokens.size() ; i++) {
        cout << tokens[i] << endl;
    }
};

void tokenizer::writeTokens() {
    ofstream file(fileName);
    file << "<tokens>" << endl;
    for (int i = 0 ; i < tokens.size() ; i++) {
        file << tokens[i] << endl;
    }
    file << "</tokens>" << endl;
};


