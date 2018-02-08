//  HexNode.hpp
//  HW6
//  Created by Morgan Scofield on 12/5/17.

#ifndef HexNode_hpp
#define HexNode_hpp

#include <stdio.h>
#include <iostream>

class HexNode{
private:
    int ID;
    int x;
    int y;
    //Using white/black instead of red/blue
    //Black = east/west, White = north/south
    int color;
public:
    
    HexNode(){};
    //Constructor
    HexNode(int a, int b);
    //Returns ID of node N
    int getID();
    //Returns x coordinate of node N
    int getX();
    //Returns y coordinate of node N
    int getY();
    //Returns color of node N
    int getColor();
    //Change color of node N
    void changeColor(int c);
    //Equals overload
    bool operator ==(const HexNode &N);
    void setID(int newID){
        ID = newID;
    };
};
#endif /* HexNode_hpp */


