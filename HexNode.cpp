//  HexNode.cpp
//  HW6
//  Created by Morgan Scofield on 12/5/17.


#include "HexNode.hpp"

HexNode::HexNode(int a, int b){
    x = a;
    y = b;
    ID = 0;
    color = 0;  //Gray --> undefined
}

int HexNode::getID(){
    return ID;
}

int HexNode::getX(){
    return x;
}

int HexNode::getY(){
    return y;
}

int HexNode::getColor(){
    return color;
}

void HexNode::changeColor(int c){
    color = c;
}

bool HexNode::operator==(const HexNode &N){
    return (this->ID == N.ID);
}


