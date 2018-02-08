//  main.cpp
//  HW6
//  Created by Morgan Scofield on 12/5/17.

#include <iostream>
#include "HexGraph.hpp"
#include "HexNode.hpp"


int main(int argc, const char * argv[]) {
    HexGraph H = HexGraph(5);
    H.playGame(H);
    H.printGraph(H);
    return 0;
}

