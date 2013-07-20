#include "graph.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <eigen3/Eigen/Eigen>

graph::graph(int numRows, int numCols){
    g.resize(numRows,numCols);
}


void graph::fill(int rowstart,int colstart,int rowlen,int collen){
    loc myLoc;
    myLoc.row = rowstart;
    myLoc.col = colstart;

    loc myLoc2;
    myLoc2.row = rowstart+rowlen-1;
    myLoc2.col = colstart+collen-1;

    graph::outOfBound(myLoc);
    graph::outOfBound(myLoc2);


    Eigen::Matrix<node,Eigen::Dynamic,Eigen::Dynamic> chunk = g.block(rowstart,colstart,rowlen,collen);
    for(int i = 0; i < chunk.rows(); i++){
        for(int j = 0; j < chunk.cols(); j++){
            chunk(i,j).value = 1;
        }
    }
    g.block(rowstart,colstart,rowlen,collen) = chunk; // not super elegant, but should work just fine.

}

void graph::clear(int rowstart, int colstart, int rowlen, int collen){
    loc myLoc;
    myLoc.row = rowstart;
    myLoc.col = colstart;

    loc myLoc2;
    myLoc2.row = rowstart+rowlen-1;
    myLoc2.col = colstart+collen-1;

    graph::outOfBound(myLoc);
    graph::outOfBound(myLoc2);


    Eigen::Matrix<node,Eigen::Dynamic,Eigen::Dynamic> chunk = g.block(rowstart,colstart,rowlen,collen);
    for(int i = 0; i < chunk.rows(); i++){
        for(int j = 0; j < chunk.cols(); j++){
            chunk(i,j).value = 0;
        }
    }
    g.block(rowstart,colstart,rowlen,collen) = chunk; // not super elegant, but should work just fine.

}

void graph::outOfBound(loc amIOutOfRange){
    if(amIOutOfRange.row < 0 || amIOutOfRange.col < 0 || amIOutOfRange.row >= g.rows() || amIOutOfRange.col >= g.cols()){
        throw "Input Out Of Range Error!";
    }
}

void graph::print(){
    for(int i = 0; i < g.rows(); i++){
        for(int j = 0; j < g.cols(); j++){
            int present = g(i,j).value;
            if(present == 0){
                std::cout<<"  ";
            }
            else{
                std::cout<<present<<" ";
            }
        }
        std::cout<<"\n";
    }

}

void graph::setStart(loc l){
    start = l;
    g(l.row,l.col).value = 3;

}

void graph::setGoal(loc l){
    goal = l;
    g(l.row,l.col).value = 4;
}

void graph::testConfig(){
    std::cout<<"You have chosen the convenient testing constructor\n";
    g.resize(10,10);
    this->fill(0,0,10,10);
    this->clear(1,1,8,8);
    this->fill(0,2,5,1);
    this->fill(0,3,5,1);
    this->fill(3,5,7,1);
    this->fill(3,6,7,1);
    loc s {6,3};
    loc gg {4,7};
    this->setStart(s);
    this->setGoal(gg);
}

