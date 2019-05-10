//
//  Syntaxer.hpp
//  Project8
//
//  Created by Kaleb Lewis on 12/3/17.
//  Copyright © 2017 Kaleb Lewis. All rights reserved.
//
#include "Tokenizer.h"
#include <set>
#include <map>

struct syntaxer {
    string fileName;
    vector<string> tokens;
    
    syntaxer(tokenizer input);
    
    void compileClass(vector<Token> intake);
    void compileClassVarDec(int &index, vector<Token> intake);
    void compileSubroutine(int &index, vector<Token> intake);
    void compileParameters(int &index, vector<Token> intake);
    void compileVarDec(int &index, vector<Token> intake);
    void compileStatement(int &index, vector<Token> intake);
    void compileDo(int &index, vector<Token> intake);
    
    
    void compileReturn(int &index, vector<Token> t);
    void compileIf(int &index, vector<Token> t);
    void compileExpression(int &index, vector<Token> t);
    void compileExpressionList(int &index, vector<Token> t);
    void compileLet(int &index, vector<Token> t);
    void compileWhile(int &index, vector<Token> t);
    void compileTerm(int &index, vector<Token> t);
    
    
    
    void printSyntax();
    void writeSyntax();
};

