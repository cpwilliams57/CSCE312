//
//  writer.h
//  Project7
//
//  Created by Kaleb Lewis on 11/25/17.
//  Copyright © 2017 Kaleb Lewis. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <fstream>

#include "parser.h"
using namespace std;


struct writer {
    //fileName is where code will be written to (XXX.asm)
    string fileName;
    //Stores asm code
    vector<string> lines;
    
    //These are used to map VM code into ASM
    map<string, string> arithMap = {{"add" , "@SP\nAM=M-1\nD=M\nM=0\n@SP\nAM=M-1\nM=D+M\n@SP\nM=M+1\n"} ,
                                    {"sub" , "@SP\nAM=M-1\nD=M\nM=0\n@R5\nM=D\n@SP\nAM=M-1\nD=M\n@R5\nD=D-M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n@R5\nM=0\n"} ,
        
        {"neg" , "@32767\nD=A\n@SP\nA=M-1\nM=D-M\nM=M+1\n"} ,
        {"eq" , "@RUN_~\n0;JMP\n(TRUE_~)\n@SP\nA=M\nM=-1\n@EQ_~\n0;JMP\n(RUN_~)\n@SP\nAM=M-1\nD=M\nM=0\n@SP\nAM=M-1\nD=D-M\nM=0\n@TRUE_~\nD;JEQ\n@SP\nA=M\nM=0\n(EQ_~)\n@SP\nM=M+1\n"} ,
        {"gt" , "@RUN_~\n0;JMP\n(TRUE_~)\n@SP\nA=M\nM=-1\n@EQ_~\n0;JMP\n(RUN_~)\n@SP\nAM=M-1\nD=M\nM=0\n@SP\nAM=M-1\nD=D-M\nM=0\n@TRUE_~\nD;JLT\n@SP\nA=M\nM=0\n(EQ_~)\n@SP\nM=M+1\n"} ,
        {"lt" , "@RUN_~\n0;JMP\n(TRUE_~)\n@SP\nA=M\nM=-1\n@EQ_~\n0;JMP\n(RUN_~)\n@SP\nAM=M-1\nD=M\nM=0\n@SP\nAM=M-1\nD=D-M\nM=0\n@TRUE_~\nD;JGT\n@SP\nA=M\nM=0\n(EQ_~)\n@SP\nM=M+1\n"} ,
        {"and" , "@SP\nAM=M-1\nD=M\nM=0\n@SP\nAM=M-1\nM=D&M\n@SP\nM=M+1\n"} ,
        {"or" , "@SP\nAM=M-1\nD=M\nM=0\n@SP\nAM=M-1\nM=D|M\n@SP\nM=M+1\n"} ,
        {"not" , "@SP\nA=M-1\nM=!M\n"}
                                    };
    
    map<string, string> memMap = {
        //push memory access commands
        //pushes value to the 7 different memory segments
        
        //push
        //@SP\nA=M\nM=D\n@SP\nM=M+1\n
        {"push constant" , "@~\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n"},
        {"push local" , "@LCL\nD=M\n@~\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n"},
        {"push argument" , "@ARG\nD=M\n@~\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n"},
        {"push this" , "@THIS\nD=M\n@~\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n"},
        {"push that" , "@THAT\nD=M\n@~\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n"},
        {"push temp" , "@R5\nD=A\n@~\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n"},
        {"push pointer", "@~\nD=A\n@3\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n"},
        {"push static", "@~\nD=A\n@16\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\n M=M+1\n"},
        
        
        
        //pop memory access commands
        //pops values from the 7 different memory segments to the main stack
        
        //pop
        //@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n
        {"pop local", "@LCL\nD=M\n@~\nD=D+A\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n"},
        {"pop argument", "@ARG\nD=M\n@~\nD=D+A\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n"},
        {"pop this", "@THIS\nD=M\n@~\nD=D+A\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n"},
        {"pop that",  "@THAT\nD=M\n@~\nD=D+A\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n"},
        {"pop temp",  "@R5\nD=A\n@~\nD=D+A\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n"},
        {"pop pointer",  "@~\nD=A\n@3\nD=D+A\n@R5\nM=D\n@SP\nAM=M-1\nD=M\n@R5\nA=M\nM=D\n" },
        {"pop static", "@~\nD=A\n@16\nD=D+A\n@R5\nM=D\n@SP\nAM=M-1\nD=M\n@R5\nA=M\nM=D\n"}
        
    
                                    };
    
    //constructor
    writer(parser input);
    
    //Translates parser VM lines into ASM
    void translate( vector<string> inputs );
    string translate(string input, int &jump);
    
    //Checks if a line is in arithMap
    bool isArith(string command);
    
    void printLines();
    void writeLines();
    
    //Fills in value for placeholder ~
    string fillIn(string source, char target, string value);
};
