//
//  main.cpp
//  Project7
//
//  Created by Kaleb Lewis on 11/24/17.
//  Copyright © 2017 Kaleb Lewis. All rights reserved.
//
#include "writer.h"

#include <iostream>
using namespace std;

int main() {
    parser test("PointerTest.vm");
    //test.printLines();
    
    writer dummy(test);
    dummy.printLines();
    dummy.writeLines();
    return 0;
}
