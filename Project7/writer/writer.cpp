//
//  writer.cpp
//  Project7
//
//  Created by Kaleb Lewis on 11/25/17.
//  Copyright © 2017 Kaleb Lewis. All rights reserved.
//

#include "writer.h"
#include <algorithm>

//Constructor uses parser to make writer
writer::writer(parser input) {
    string temp = input.fileName;
    fileName = temp.substr(0, temp.length() - 3) + ".asm";
    
    translate(input.lines);
};



//Takes lines of VM code and translates to asm, stores in writer lines variable
void writer::translate(vector<string> inputs) {
    string line;
    int jump = 0;
    for (int i = 0 ; i < inputs.size() ; i++) {
        line = translate(inputs[i], jump);
        lines.push_back(line);
    }
};



//Translates individual vm line into asm code
string writer::translate(string input, int &jump) {
    string asmCode, memAccess, value;
    
    if (isArith(input)) {
        asmCode += arithMap[input];
        if ((input == "eq") || (input == "gt") || (input == "lt")) {
            value = to_string(jump);
            asmCode = fillIn(asmCode, '~', value);
            jump++;
        }
        return asmCode;
    }
    else {
        //Grabs push or pop, then shrinks input string
        memAccess = input.substr(0, input.find(" ") + 1);
        input = input.substr(input.find(" ") + 1, input.length());
        
        //Grabs constant, local, etc. and strinks input string
        memAccess += input.substr(0, input.find(" "));
        input = input.substr(input.find(" ") + 1, input.length());
        
        //Adds asm mapping to asmCode
        asmCode += memMap[memAccess];
        
        //Grabs the value being pushed/popped and swaps it in for placeholder '~' char
        value = input;
        asmCode = fillIn(asmCode, '~', value);
    }
    
    return asmCode;
};



//Checks if a line is in the arithMap, meaning it's an arithmetic command
bool writer::isArith(string command) {
    return (arithMap.find(command) != arithMap.end());
};

//Fills in placehold ~ for value being used
string writer::fillIn(string source, char target, string value) {
    for (int i = 0 ; i < source.length() ; i++) {
        if (source[i] == target) {
            source = source.substr(0, i) + value + source.substr(i + 1, source.length());
        }
    }
    return source;
};


void writer::writeLines() {
    ofstream file(fileName);
    cout << fileName << endl;
    for (int i = 0 ; i < lines.size() ; i++){
        file << lines[i];
    }
};



//Internal use, I put an extra endl for readability
void writer::printLines() {
    for (int i = 0 ; i < lines.size() ; i++) {
        cout << lines[i] << endl;
    }
};
