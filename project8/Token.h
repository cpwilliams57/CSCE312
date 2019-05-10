//
//  Token.hpp
//  Project8
//
//  Created by Kaleb Lewis on 11/27/17.
//  Copyright © 2017 Kaleb Lewis. All rights reserved.
//

#include <iostream>

using namespace std;

struct Token {
    string value;
    string kind;
    int priority;
    
    Token();
    Token(string tokenValue, string tokenKind);
    Token(char tokenValue, string tokenKind);
    friend ostream& operator<<(ostream& os, const Token& tk);
    string str();
};
