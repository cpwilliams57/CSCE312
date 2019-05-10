//
//  Token.cpp
//  Project8
//
//  Created by Kaleb Lewis on 11/27/17.
//  Copyright © 2017 Kaleb Lewis. All rights reserved.
//

#include "Token.h"
#include <sstream>
Token::Token() {
    value;
    kind;
    priority = 0;
};

Token::Token(string tokenValue, string tokenKind) {
    value = tokenValue;
    kind = tokenKind;
    priority = 0;
};

Token::Token(char tokenValue, string tokenKind) {
    value = tokenValue;
    kind = tokenKind;
    priority = 0;
};

//keywords
//identifiers
//symbols
//constants (str & int)


//Output operator
ostream& operator<<(ostream& os, const Token& tk){
    for (int i = 0 ; i < tk.priority ; i++) {
        os << "   ";
    }
    os << "<" << tk.kind << "> " << tk.value << " </" << tk.kind << ">";
    return os;
};

string Token::str() {
    stringstream temp;
    temp << *this;
    return temp.str();
};
