//
//  Parser.h
//  Project7
//
//  Created by Kaleb Lewis on 11/24/17.
//  Copyright © 2017 Kaleb Lewis. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct parser {
    //fileName is where we read VM code from
    string fileName;
    //This stores VM code
    vector<string> lines;
    
    //Constructor
    parser(string fileInput);
    
    //Reads each line and adds it to lines
    void readLines();
    //Removes comments from each line
    string scanLine(string line);
    
    //Internal use, prints lines for testing
    void printLines();
};

