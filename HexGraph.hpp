//  HexGraph.hpp
//  HW6
//  Created by Morgan Scofield on 12/5/17.

#ifndef HexGraph_hpp
#define HexGraph_hpp

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <stack>
#include <random>
#include <iterator>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include "HexNode.hpp"

//using namespace std;

class HexGraph{
private:
    int rowNodes;
    int nodeCount;
    int edgeCount;
    std::vector<std::deque<int> > edgeList;
    
public:
    //Constructor
    HexGraph(int n);
    //Initializes the nodes randomly
    void playGame(HexGraph &G);
    //Pick the best move found with the minimax function
    int findBestMove(HexGraph &G);
    //Monte-Carlo evaluation of graph
    double MonteCarlo(HexGraph &G, int currPos);
    //Random eval of board, MonteCarlo helper function
    void randomize(HexGraph &G, int currPos);
    //Runs DFS on black or white nodes
    int DFS(HexGraph &G, std::vector<HexNode> input, int turn);
    //DFS helper function
    int dfsHelper(HexGraph &G, std::vector<HexNode> input, std::vector<bool> v, int s, std::vector<int>& stack, int index, int color);
    //Returns degree of edges
    int E();
    //Returns degree of edges
    int V();
    //Returns number of nodes per column/row
    int N();
    //Seeds random number
    std::mt19937 make_seeded_engine();
    //Print graph
    void printGraph(HexGraph &G);
    
    //Player turn: Black = 1, White = 0
    int pTurn;
    //State of game
    bool isOver = false;;
    //List of nodes
    std::vector<HexNode> nodeList;
    //Black Nodes
    std::vector<HexNode> blackList;
    //White Nodes
    std::vector<HexNode> whiteList;
    //Vectors for counting wins for each space
    std::vector<double> bWins;
    std::vector<double> wWins;
    
    std::mt19937 generator;
};

#endif /* HexGraph_hpp */


