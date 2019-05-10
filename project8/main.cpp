//
//  main.cpp
//  Project8
//
//  Created by Kaleb Lewis on 11/27/17.
//  Copyright © 2017 Kaleb Lewis. All rights reserved.
//

#include <iostream>
#include "Syntaxer.h"

using namespace std;



int main(int argc, char *argv[]) {
    
   if (argc != 2){
        cout << "Please give me a file my dude" << endl;
    }
    else {
        string fileName = argv[1];
        tokenizer inputs(fileName);

        inputs.writeTokens();

        syntaxer outputs(inputs);

        outputs.writeSyntax();
        
        
        
    }
    
    return 0;
}
