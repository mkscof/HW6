//  HexGraph.cpp
//  HW6
//  Created by Morgan Scofield on 12/5/17.

#include "HexGraph.hpp"

HexGraph::HexGraph(int n){
    int count = 0;
    rowNodes = n;
    nodeCount = n * n;
    edgeCount = 0;
    edgeList.resize(nodeCount);
    
    generator = make_seeded_engine();
    
    for(int i = 0; i < nodeCount; i++){
        bWins.push_back(false);
        wWins.push_back(false);
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            nodeList.push_back(HexNode(i, j));
            if(i == 0){
                //top left corner
                if(j == 0){
                    edgeList[count].push_front(i * n + j + 1);
                    edgeList[count].push_front((i + 1) * n + j);
                    edgeCount = edgeCount + 2;
                }
                //top right corner
                else if(j == n - 1){
                    edgeList[count].push_front(i * n + j - 1);
                    edgeList[count].push_front((i + 1) * n + j);
                    edgeList[count].push_front((i + 1) * n + j - 1);
                    edgeCount = edgeCount + 3;
                }
                //top edge
                else if(j != 0 && j != n - 1){
                    edgeList[count].push_front(i * n + j + 1);
                    edgeList[count].push_front((i + 1) * n + j);
                    edgeList[count].push_front(i * n + j - 1);
                    edgeList[count].push_front((i + 1) * n + j - 1);
                    edgeCount = edgeCount + 4;
                }
            }
            else if(i == n - 1){
                //bottom left corner
                if(j == 0){
                    edgeList[count].push_front((i - 1) * n + j);
                    edgeList[count].push_front((i - 1) * n + j + 1);
                    edgeList[count].push_front(i * n + j + 1);
                    edgeCount = edgeCount + 3;
                }
                //bottom right corner
                else if(j == n - 1){
                    edgeList[count].push_front((i - 1) * n + j);
                    edgeList[count].push_front(i * n + j - 1);
                    edgeCount = edgeCount + 2;
                }
                //bottom edge
                else if(j != 0 && j != n - 1){
                    edgeList[count].push_front((i - 1) * n + j);
                    edgeList[count].push_front(i * n + j - 1);
                    edgeList[count].push_front((i - 1) * n + j + 1);
                    edgeList[count].push_front(i * n + j + 1);
                    edgeCount = edgeCount + 4;
                }
            }
            else if(i != 0 && i != n - 1){
                //left edge
                if(j == 0){
                    edgeList[count].push_front(i * n + j + 1);
                    edgeList[count].push_front((i + 1) * n + j);
                    edgeList[count].push_front((i - 1) * n + j);
                    edgeList[count].push_front((i - 1) * n + j + 1);
                    edgeCount = edgeCount + 4;
                }
                //right edge
                else if(j == n - 1){
                    edgeList[count].push_front(i * n + j - 1);
                    edgeList[count].push_front((i + 1) * n + j);
                    edgeList[count].push_front((i + 1) * n + j - 1);
                    edgeList[count].push_front((i - 1) * n + j);
                    edgeCount = edgeCount + 4;
                }
                //inner node
                else{
                    edgeList[count].push_front(i * n + j + 1);
                    edgeList[count].push_front((i + 1) * n + j);
                    edgeList[count].push_front(i * n + j - 1);
                    edgeList[count].push_front((i + 1) * n + j - 1);
                    edgeList[count].push_front((i - 1) * n + j);
                    edgeList[count].push_front((i - 1) * n + j + 1);
                    edgeCount = edgeCount + 6;
                }
            }
            count++;
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            nodeList.at(i * n + j).setID(i * n + j);
        }
    }
}

void HexGraph::playGame(HexGraph &G){
    pTurn = 1;
    int pX, pY, pM, cM;     //  Player/Computer move coordinates
    
    while(!isOver){
        //Player turn
        if(pTurn % 2 == 1){
            std::cout << "Enter x, y coordinates of move (0-" << G.N() << " separated by spaces)";
            std::cin >> pX >> pY;
            if(!std::cin){
                std::cerr << "Invalid input";
            }
            else if(pX > G.N() || pX < 0 || pY > G.N() || pY < 0){
                std::cerr << "Out of bounds input value";
                continue;
            }
            else if(nodeList.at(pX * G.N() + pY).getColor() != 0){
                std::cout << "Tile already played in this space" <<std::endl;
                continue;
            }
            pM = (pX * G.N() + pY);
            
            nodeList.at(pM).changeColor(1);
            blackList.push_back(nodeList.at(pM));
            int check = DFS(G, blackList, pTurn);
            if(check == 1){
                std::cout << "Black Wins" << std::endl;
                std::cout << nodeList.at(0).getID();
                isOver = true;
                break;
            }
            pTurn++;
            std::cout << "Black (Player) Turn:" << std::endl;
            printGraph(G);
        }
        //Computer turn
        else if(pTurn % 2 == 0){
            cM = findBestMove(G);
            nodeList.at(cM).changeColor(-1);
            whiteList.push_back(nodeList.at(cM));
            int check = DFS(G, whiteList, pTurn);
            if(check == -1){
                std::cout << "White Wins" << std::endl;
                isOver = true;
                break;
            }
            pTurn++;
            std::cout << "White (Computer) Turn:" << std::endl;
            printGraph(G);
        }
    }
}

int HexGraph::findBestMove(HexGraph &G){
    int best = -1000;
    double bMove = -1000;
    for(int i = 0; i < G.N(); i++){
        for(int j = 0; j < G.N(); j++){
            int cIndex = i * G.N() + j;
            //If empty space
            if(nodeList.at(cIndex).getColor() == 0){
                double cMove = abs(MonteCarlo(G, cIndex));
                //If this move is better update best move
                if(cMove > bMove){
                    bMove = cMove;
                    best = cIndex;
                }
            }
        }
    }
    return best;
}

double HexGraph::MonteCarlo(HexGraph &G, int currPos){
    double move;
    //Perform MonteCarlo trials on current position
    for(int i = 0; i < 1000; i++){
        randomize(G, currPos);
    }
    if(bWins.at(currPos) > wWins.at(currPos)){
        move = bWins.at(currPos) - wWins.at(currPos);
    }
    else{
        move = wWins.at(currPos) - bWins.at(currPos);
    }
    return move;
}

void HexGraph::randomize(HexGraph &G, int x){
    bWins.at(x) = 0;
    wWins.at(x) = 0;
    int tempTurn = pTurn;
    std::vector<HexNode> tempList;
    tempList = nodeList;
    
    std::vector<int> shuffled;
    for(int i = 0; i < G.V(); i++){
        shuffled.push_back(i);
    }
    //Seed random generator and shuffle nodes
//    std::random_shuffle(shuffled.begin(), shuffled.end());
    std::shuffle(shuffled.begin(), shuffled.end(), generator);
    for(auto i = shuffled.begin(); i != shuffled.end(); i++){
        int curr = *i;
        //Change to black
        if(tempTurn % 2 == 1){
            if(tempList.at(curr).getColor() == 0){
                tempList.at(curr).changeColor(1);
            }
            tempTurn++;
        }
        //Change to white
        else if(tempTurn % 2 == 0){
            if(tempList.at(curr).getColor() == 0){
                tempList.at(curr).changeColor(-1);
            }
            tempTurn++;
        }
    }
    int check = DFS(G, tempList, pTurn);
    if(check == 1){
        bWins.at(x)++;
    }
    else if(check == -1){
        wWins.at(x)++;
    }
}

int HexGraph::DFS(HexGraph &G, std::vector<HexNode> input, int turn){
    std::vector<bool> visited(input.size(), false);
    std::vector<int> stack;
    int helpCheck = 0;
    
    if(turn > G.V()){
        for(int i = 0; i < input.size(); i++){
            if(input.at(i).getX() == 0 && input.at(i).getColor() == -1){
                helpCheck = dfsHelper(G, input, visited, input.at(i).getID(), stack, i, -1);
            }
        }
        for(int j = 0; j < input.size(); j++){
            if(input.at(j).getY() == 0 && input.at(j).getColor() == 1){
                helpCheck = dfsHelper(G, input, visited, input.at(j).getID(), stack, j, 1);
            }
        }
    }
    
    //If turn = white
    else if(turn % 2 == 0){
        //Add nodes on top edge of graph to vector
        for(int i = 0; i < input.size(); i++){
            if(input.at(i).getX() == 0 && input.at(i).getColor() == -1){
                helpCheck = dfsHelper(G, input, visited, input.at(i).getID(), stack, i, -1);
            }
        }
    }
    //If turn = black
    else if(turn % 2 == 1){
        //Add nodes on left edge of graph to vector
        for(int i = 0; i < input.size(); i++){
            if(input.at(i).getY() == 0 && input.at(i).getColor() == 1){
                helpCheck = dfsHelper(G, input, visited, input.at(i).getID(), stack, i, 1);
            }
        }
    }
    return helpCheck;
}

int HexGraph::dfsHelper(HexGraph &G, std::vector<HexNode> input, std::vector<bool> v, int s, std::vector<int>& stack, int index, int color){
    
    stack.push_back(s);
    v[index] = true;
    int val = 0;
    
    if(color == 1){
        if(s % G.N() == G.N() - 1){
            return 1;
        }
    }
    else if(color == -1){
        if(s / G.N() == G.N() - 1){
            return -1;
        }
    }
    for(int i = 0; i < edgeList[s].size(); i++){
        HexNode node;
        node.setID(edgeList[s].at(i));
        std::vector<HexNode>::iterator iter = find(input.begin(), input.end(), node);
        int dIndex = distance(input.begin(), iter);
        if (iter != input.end() && v[dIndex] != true && input.at(dIndex).getColor() == color){
            val = dfsHelper(G, input, v, edgeList[s].at(i), stack, dIndex, color);
        }
    }
    return val;
}

std::mt19937 HexGraph::make_seeded_engine(){
//    unsigned seed = static_cast<int>(time(0));
//    return std::mt19937(seed);
    std::vector<unsigned int> random_data(624);
    std::random_device source;
    std::generate(begin(random_data), end(random_data), [&](){return source();});
    std::seed_seq seeds(begin(random_data), end(random_data));
    std::mt19937 seededEngine (seeds);
    return seededEngine;
}

int HexGraph::E(){
    return edgeCount;
}

int HexGraph::V(){
    return nodeCount;
}

int HexGraph::N(){
    return rowNodes;
}

void HexGraph::printGraph(HexGraph &G){
    std::string indent = " ";
    int count = 0;
    for(int i = 0; i < nodeList.size(); i++){
        if(nodeList.at(i).getColor() == -1){       //White
            std::cout << "◦ ";
            count++;
        }
        else if(nodeList.at(i).getColor() == 1){  //Black
            std::cout << "● ";
            count++;
        }
        else if(nodeList.at(i).getColor() == 0){  //Gray
            std::cout << "# ";
            count++;
        }
        if(count % G.N() == 0){
            std::cout << std::endl;
            std::cout << indent;
            indent.append(" ");
        }
    }
}

