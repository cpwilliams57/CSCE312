//
//  Syntaxer.cpp
//  Project8
//
//  Created by Kaleb Lewis on 12/3/17.
//  Copyright © 2017 Kaleb Lewis. All rights reserved.
//

#include "Syntaxer.h"
#include <sstream>
#include <stack>

syntaxer::syntaxer(tokenizer input) {
    string temp = input.fileName;
    fileName = temp.substr(0, temp.length() - 9) + "Parser.xml";
    
    
    
    compileClass(input.tokens);
};

void syntaxer::compileClass(vector<Token> intake) {
    Token currToken;
    tokens.push_back("<class>");
    string currValue;
    for (int i = 0; i < intake.size() ; i++) {
        currToken = intake[i];
        currValue = currToken.value;
        if ((currValue == "static") || (currValue == "field")) {
            compileClassVarDec(i, intake);
        }
        else if ((currValue == "function") || (currValue == "method") || (currValue == "constructor")) {
            compileSubroutine(i, intake);
        }
        else {
            tokens.push_back(currToken.str());
        }
    }
    tokens.push_back("</class>");
};

void syntaxer::compileClassVarDec(int &index, vector<Token> intake) {
    tokens.push_back("<classVarDec>");
    
    tokens.push_back(intake[index].str());
    index++;
    tokens.push_back(intake[index].str());
    index++;
    while ((intake[index].value != ";")) {
        tokens.push_back(intake[index].str());
        index++;
    }
    tokens.push_back(intake[index].str());
    index++;
    /*
    for (int h = 0; h < 4 ; h++) {
        tokens.push_back(intake[h + index].str());
        index++;
    }
     */
    tokens.push_back("</classVarDec>");
};

void syntaxer::compileSubroutine(int &index, vector<Token> intake) {
    tokens.push_back("<subroutineDec>");
    for (int h = 0; h < 4 ; h++) {
        tokens.push_back(intake[h + index].str());
    }
    index = index + 4;
    
    compileParameters(index, intake);
    
    tokens.push_back(intake[index].str());
    index++;
    
    tokens.push_back("<subroutineBody>");
    
    
    tokens.push_back(intake[index].str());
    index++;
    while (intake[index].value == "var") {
        compileVarDec(index, intake);
    }
    //tokens.push_back(intake[index].str());
    //index++;
    //while (intake[index].value != "}") {
        compileStatement(index, intake);
    
    
    //}
    tokens.push_back(intake[index].str());
    index++;
    
    tokens.push_back("</subroutineBody>");
    tokens.push_back("</subroutineDec>");
};

void syntaxer::compileParameters(int &index, vector<Token> intake) {
    tokens.push_back("<parameterList>");
    while (intake[index].value != ")") {
        tokens.push_back(intake[index].str());
        index++;
    }
    tokens.push_back("</parameterList>");
    tokens.push_back(intake[index].str());
    index++;
};

void syntaxer::compileVarDec(int &index, vector<Token> intake) {
    tokens.push_back("<varDec>");
    while (intake[index].value != ";") {
        tokens.push_back(intake[index].str());
        index++;
    }
    tokens.push_back(intake[index].str());
    index++;
    tokens.push_back("</varDec>");
};

void syntaxer::compileStatement(int &index, vector<Token> intake) {
    tokens.push_back("<statements>");
    string stateType = intake[index].value;
    while ((intake[index].value == "let") || (intake[index].value == "if") || (intake[index].value == "while") || (intake[index].value == "do") || (intake[index].value == "return")) {
        
        string stateType = intake[index].value;
        if (stateType == "let") {
            compileLet(index, intake);
        }
        else if (stateType == "if") {
            compileIf(index, intake);
        }
        else if (stateType == "while") {
            compileWhile(index, intake);
        }
        else if (stateType == "do") {
            compileDo(index, intake);
        }
        else if (stateType == "return") {
            compileReturn(index, intake);
        }
    }
    tokens.push_back("</statement>");
};

void syntaxer::compileDo(int &index, vector<Token> intake) {
    tokens.push_back("<doStatement>");
    while (intake[index].value != ";") {
        tokens.push_back(intake[index].str());
        index++;
    }
    tokens.push_back("</doStatement>");
}

//compiles Let statements
void syntaxer::compileLet(int &index, vector<Token> t){
    tokens.push_back("<letStatement>");
    
    tokens.push_back(t[index].str()); // <keyword> let </keyword>
    index++;
    
    tokens.push_back(t[index].str());
    index++;
    
    //handle let statements
    if (t[index].value == "[") {
        tokens.push_back(t[index].str());
        index++;
        compileExpression(index, t);
        tokens.push_back(t[index].str());
        index++;
    }
    tokens.push_back(t[index].str());
    index++;
    compileExpression(index, t);
    tokens.push_back(t[index].str());
    //index++;
    
    tokens.push_back("</letStatement>");
    
};

//compiles terms
void syntaxer::compileTerm(int &index, vector<Token> t){
    tokens.push_back("<term>");
    // determine what kind of term
    if ((t[index].value == "~") || (t[index].value == "-")) {
        tokens.push_back(t[index].str());
        index++;
        compileTerm(index, t);
    }
    else if (t[index].value == "(") {
        tokens.push_back(t[index].str());
        index++;
        compileExpression(index, t);
        tokens.push_back(t[index].str());
        index++;
    }
    else {
        tokens.push_back(t[index].str());
        index++;
        
        if (t[index].value == "[") {
            tokens.push_back(t[index].str());
            index++;
            compileExpression(index, t);
            tokens.push_back(t[index].str());
            index++;
        }
        else if (t[index].value == ".") {
            tokens.push_back(t[index].str());
            index++;
            tokens.push_back(t[index].str());
            index++;
            tokens.push_back(t[index].str());
            index++;
            compileExpressionList(index, t);
            tokens.push_back(t[index].str());
            index++;
        }
        else if (t[index].value == "(") {
            tokens.push_back(t[index].str());
            index++;
            compileExpressionList(index, t);
            tokens.push_back(t[index].str());
            index++;
            
        }
        
    }
    tokens.push_back("</term>");
};

//compiles while statements
void syntaxer::compileWhile(int &index, vector<Token> t){
    tokens.push_back("<whileStatement>");
    tokens.push_back(t[index].str()); // <keyword> while </keyword>
    index++;
    tokens.push_back(t[index].str()); // <symbol> ( </symbol>
    index++;
    compileExpression(index, t); // handling while condition
    tokens.push_back(t[index].str()); // <symbol> ) </symbol>
    index++;
    
    compileStatement(index, t);
    
    tokens.push_back(t[index].str()); // <symbol> } </symbol>
    index++;
    
    tokens.push_back("</whileStatement>");
};

//compiles return statements
void syntaxer::compileReturn(int &index, vector<Token> t){
    tokens.push_back("<returnStatement>");
    tokens.push_back(t[index].str());
    index++;
    tokens.push_back(t[index].str());
    index++;
    tokens.push_back("</returnStatement>");
    index = index + 2;
};

//compiles if statements
void syntaxer::compileIf(int &index, vector<Token> t){
    tokens.push_back("<ifStatement>");
    tokens.push_back(t[index].str()); // <keyword> if </keyword>
    index++;
    tokens.push_back(t[index].str()); // <symbol> ( </symbol>
    index++;
    compileExpression(index, t); // handling if condition
    tokens.push_back(t[index].str()); // <symbol> ) </symbol>
    index++;
    tokens.push_back(t[index].str()); // <symbol> { </symbol>
    index++;
    
    compileStatement(index, t);
    
    tokens.push_back(t[index].str()); // <symbol> } </symbol>
    index++;
    
    tokens.push_back("</ifStatement>");
    
};

//compiles exxpressions
void syntaxer::compileExpression(int &index, vector<Token> t){
    
    tokens.push_back("<expression>");
    
    compileTerm(index, t);  //
    set<string> op = {{"+"}, {"-"}, {"*"}, {"/"}, {"&amp;"}, {"\\"}, {"|"}, {"&lt;"}, {"&gt;"}, {"="}};
    while (op.find(t[index].value) != op.end()) {
        tokens.push_back(t[index].str()); // <symbol> } </symbol>
        index++;
        compileTerm(index, t);
    }
    tokens.push_back("</expression>");
};

//compiles return statements
void syntaxer::compileExpressionList(int &index, vector<Token> t){
    tokens.push_back("<expressionList>");
    
    if (t[index].value != ")") {
        compileExpression(index, t);
    }
    
    while (t[index].value != ")") {
        tokens.push_back(t[index].str());
        index++;
        compileExpression(index, t);
    }
    
    tokens.push_back("</expressionList>");
};



void syntaxer::printSyntax() {
    for (int i = 0 ; i < tokens.size() ; i++) {
        cout << tokens[i] << endl;
    }
};

void syntaxer::writeSyntax() {
    ofstream file(fileName);
    for (int i = 0 ; i < tokens.size() ; i++) {
        file << tokens[i] << endl;
    }
};
