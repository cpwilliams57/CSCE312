//
//  Parser.cpp
//  Project7
//
//  Created by Kaleb Lewis on 11/24/17.
//  Copyright © 2017 Kaleb Lewis. All rights reserved.
//

#include "parser.h"

#include <iostream>
#include <vector>
#include <fstream>

parser::parser(string fileInput) {
    fileName = fileInput;
    readLines();
};


void parser::readLines() {
    fstream file(fileName);
    
    string fileLine;
    
    while (file.good()) {
        getline(file, fileLine, '\n');
        
        fileLine = scanLine(fileLine);
        
        if ((fileLine != "") && (fileLine.length() > 1)){
            lines.push_back(fileLine);
        }
    }
};


string parser::scanLine(string line) {
    string scannedLine;
    char curr, next = '\0';
    
    line = line.substr(0, line.length() - 1);
    
    for (int i = 0 ; i < line.length() ; i++) {
        curr = line[i];
        
        if (i < (line.size() - 1)) {
            next = line[i + 1];
        }
        
        if ((curr == '/') && (next == '/')) {
            return scannedLine;
        }
        else {
            scannedLine += curr;
        }
    }
    return scannedLine;
};

void parser::printLines() {
    for (int i = 0 ; i < lines.size() ; i++) {
        cout << lines[i] << endl;
    }
};
