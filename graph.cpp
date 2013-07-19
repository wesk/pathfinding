#include "graph.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <vector>

graph::graph()
{

}

node graph::getNode(int row, int col){
    if(outOfBound(row) || outOfBound(col) ){
        std::cout<<"ALERT! OUT OF BOUND!"<<std::endl;
    }
    return g[row][col];
}

void graph::print(){
    int size = sqrt(sizeof(g) / sizeof(node));
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            std::cout<<getNode(i,j).value;
        }
        std::cout<<"\n";
    }
}

bool graph::outOfBound(int amIOutOfRange){
    bool state = false;
    int size = sqrt(sizeof(g) / sizeof(node));
    if( (amIOutOfRange < 0) || (amIOutOfRange >= size)){
        state = true;
    }
    return state;
}

void graph::fill(int rowstart, int colstart, int rowlen, int collen){
    if((outOfBound(rowstart) || outOfBound(colstart) || outOfBound(rowstart+rowlen-1) || outOfBound(colstart+collen-1))){
        std::cout<<"ALERT!!!!"<<std::endl;
    }
    for(int i = colstart; i < colstart+collen; i++){
        for(int j = rowstart; j < rowstart+rowlen; j++){
            g[j][i].value = 1;
        }
    }
}

void graph::clear(int rowstart, int colstart, int rowlen, int collen){
    if((outOfBound(rowstart) || outOfBound(colstart) || outOfBound(rowstart+rowlen) || outOfBound(colstart+collen))){
        std::cout<<"ALERT!!!!"<<std::endl;
    }
    for(int i = colstart; i < colstart+collen; i++){
        for(int j = rowstart; j < rowstart+rowlen; j++){
            g[j][i].value = 0;
        }
    }
}

void graph::setStart(int row, int col){
    g[row][col].value = 3;
    g[row][col].distance = 0;
    start.row = row;
    start.col = col;
}

void graph::setGoal(int row, int col){
    g[row][col].value = 4;
    goal.row = row;
    goal.col = col;
}

node graph::getStart(){
    return g[start.row][start.col];
}

node graph::getGoal(){
    return g[goal.row][goal.col];
}


