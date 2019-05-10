//
//  Tokenizer.hpp
//  Project8
//
//  Created by Kaleb Lewis on 11/27/17.
//  Copyright © 2017 Kaleb Lewis. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <map>
#include <stack>
#include <queue>

#include "Token.h"

using namespace std;

struct tokenizer {
    //fileName is where we jack code from
    string fileName;
    //This stores jack code
    vector<Token> tokens;
    
    map<char, string> equalSet = { {'<', "&lt;"}, {'>', "&gt;"}, {'&', "&amp;"}};
    set<char> symbolSet = {'{', '}', '(', ')', '[', ']', '.', ',', ';', '+', '-', '*', '/', '&', '|', '<', '>', '=', '~'};
    set<string> keySet = {"class", "constructor", "function", "method", "field", "static", "var", "int", "char", "boolean", "void", "true", "false", "null", "this", "let", "do", "if", "else", "while", "return"};
    
    //Constructor
    tokenizer(string fileInput);
    
    //Reads each line and adds it to lines
    void readTokens(string fileIn);
    //Removes comments & spaces from each line
    string scanLine(string line, bool &comment);
    void makeTokens(string line);
    Token idToken(queue<char> &parseQueue);
    
    bool isSymbol(char input);
    bool isKeyword(string input);
    bool isInt(string input);
    bool isSpecial(char input);
    
    
    //Internal use, prints tokens for testing
    void printTokens();
    void writeTokens();
    
};


