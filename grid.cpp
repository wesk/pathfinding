#include "grid.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <eigen3/Eigen/Eigen>
#include <iomanip>

grid::grid(int numRows, int numCols){
    g.resize(numRows,numCols);
}

void grid::fill(int rowstart,int colstart,int rowlen,int collen){
    loc myLoc;
    myLoc.row = rowstart;
    myLoc.col = colstart;

    loc myLoc2;
    myLoc2.row = rowstart+rowlen-1;
    myLoc2.col = colstart+collen-1;

    grid::outOfBound(myLoc);
    grid::outOfBound(myLoc2);


    Eigen::Matrix<node,Eigen::Dynamic,Eigen::Dynamic> chunk = g.block(rowstart,colstart,rowlen,collen);
    for(int i = 0; i < chunk.rows(); i++){
        for(int j = 0; j < chunk.cols(); j++){
            chunk(i,j).value = 1;
            chunk(i,j).visited = true; //Important! See grid::getAllActiveUnfinalized for why
        }
    }
    g.block(rowstart,colstart,rowlen,collen) = chunk; // not super elegant, but should work just fine.

}

void grid::clear(int rowstart, int colstart, int rowlen, int collen){
    loc myLoc;
    myLoc.row = rowstart;
    myLoc.col = colstart;

    loc myLoc2;
    myLoc2.row = rowstart+rowlen-1;
    myLoc2.col = colstart+collen-1;

    grid::outOfBound(myLoc);
    grid::outOfBound(myLoc2);


    Eigen::Matrix<node,Eigen::Dynamic,Eigen::Dynamic> chunk = g.block(rowstart,colstart,rowlen,collen);
    for(int i = 0; i < chunk.rows(); i++){
        for(int j = 0; j < chunk.cols(); j++){
            chunk(i,j).value = 0;
            chunk(i,j).visited = false;
        }
    }
    g.block(rowstart,colstart,rowlen,collen) = chunk; // not super elegant, but should work just fine.

}

void grid::outOfBound(loc amIOutOfRange){

    if(amIOutOfRange.row < 0 || amIOutOfRange.col < 0 || amIOutOfRange.row >= g.rows() || amIOutOfRange.col >= g.cols()){
        std::cout<<"THE PROGRAM WILL CRASH, outOfBound detects an out-of-grid-range loc!\n";
        std::cout<<amIOutOfRange.row<<" "<<amIOutOfRange.col<<std::endl;
    }
}

void grid::print(){
    for(int i = 0; i < g.rows(); i++){
        for(int j = 0; j < g.cols(); j++){
            int present = g(i,j).value;
            if(present == 0){
                std::cout<<"  ";
            }
            else if(present == 2){
                std::cout<<(char)0x40<<" ";
            }
            else{
                std::cout<<present<<" ";
            }
        }
        std::cout<<"\n";
    }
}

void grid::printEverything(){

    std::cout<<"~~~~~~~~~~~~~~~~~~~distance~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    for(int i = 0; i < g.rows(); i++){
        for(int j = 0; j < g.cols(); j++){
            double present = g(i,j).distance;
            std::cout<<std::setw(5)<< present<<" ";

        }
        std::cout<<("\n");
        std::cout<<"\n";
    }
    std::cout<<"~~~~~~~~~~~~~~~~~visited~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    for(int i = 0; i < g.rows(); i++){
        for(int j = 0; j < g.cols(); j++){
            bool present = g(i,j).visited;
            std::cout<<present<<" ";
        }
        std::cout<<"\n";
    }
    std::cout<<"~~~~~~~~~~~~~~~~~loc of previous~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    for(int i = 0; i < g.rows(); i++){
        for(int j = 0; j < g.cols(); j++){
            loc present = g(i,j).locOfPrevious;
            std::cout<<std::setw(3)<<present.row<<" "<<present.col<<" ";
        }
        std::cout<<"\n";
        std::cout<<"\n";
    }
    std::cout<<"~~~~~~~~~~~~~~~~~~~~~value:~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    this->print();
}

void grid::setStart(loc l){
    start = l;
    g(l.row,l.col).value = 3;
    this->setNodeDistance(l,0);

}

void grid::setGoal(loc l){
    goal = l;
    g(l.row,l.col).value = 4;
}

loc grid::getStart(){
    return start;
}

loc grid::getGoal(){
    return goal;
}

void grid::testConfig(){
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

bool grid::areAdjacent(loc a, loc b){

    outOfBound(a);
    outOfBound(b);
    //if(!(a.row == b.row && a.col == b.col)){  // Special case: should return true, even if a and b are the same
        if(((abs(a.row-b.row)) <= 1) && (abs(a.col-b.col) <= 1)){
            return true;
        }
    //}
    return false;
}

double grid::calcDist(loc a, loc b){ // Precondition: Must be Adjacent! true is diagonal, false is orthogonal.

    if(areAdjacent(a,b)){
        if((abs(a.row-b.row) == 1) && (abs(a.col-b.col) == 1)){
            return 1.4; //Diagonal Case
        }

        if(abs(a.row-b.row) == 1){ // not elegant, but if a and b are the same, will return a super high distance.
            return 1;
        }
        if(abs(a.col-b.col) == 1){
            return 1;
        }
        return 99999999; //a and b are the same.
    }
    std::cout<<"Something funky is going on here, fix the problem!\n";
    return 9999999;

}


// Here are the more important methods:

std::vector<loc> grid::calcDistOfAllValidAdj(loc l){  // This could return a vector of locs, to pass to another function, instead of getAllActiveUnfinalized

    outOfBound(l);
    //std::cout<<"in calcDistOfAllValidAjd method, current loc is: "<<l.row<<" "<<l.col<<std::endl;
    int rowstart,rowend,colstart,colend;
    rowstart = l.row;
    rowend = l.row;
    colstart = l.col;
    colend = l.col;
    if(l.row > 0){
        rowstart = l.row-1;
    }
    if(l.col > 0){
        colstart = l.col-1;
    }
    if(l.row < (g.rows()-1)){
        rowend = l.row+1;
    }
    if(l.col < (g.cols()-1)){
        colend = l.col+1;
    }
    //int numberoflocs = 0;

    std::vector<loc> listOfNewLocs;

    for(int r = rowstart; r <= rowend; r++){// <=, not just <
        for(int c = colstart; c <= colend; c++){
            if(!(g(r,c).value == 1)){// anything but 1. 1 means full. //Clean up syntax here, use the setNode.. getNode... blablalba
                if(g(r,c).distance == -1){ // if it hasn't been visited yet, this updates the new distance. Otherwise, see the else statement for distance check.
                    this->setNodeDistance({r,c},this->getNodeDistance(l)+this->calcDist(l,{r,c}));
                    //std::cout<<this->getNodeDistance(l)+this->calcDist(l,{r,c})<<" in calcDistOfAllValidAdj func "<<std::endl;
                    this->setNodeLocToPrevious(l,{r,c});
                    listOfNewLocs.push_back({r,c}); // adds the loc to the new list of where to still search
                }
                else{ // If it has been visited, check to see if this way is shorter. if so, update  like the previous two lines. else, do nothing.
                    if(this->getNodeDistance({r,c}) > this->getNodeDistance(l)+this->calcDist(l,{r,c})){
                        this->setNodeDistance({r,c},this->getNodeDistance(l)+this->calcDist(l,{r,c}));
                        this->setNodeLocToPrevious(l,{r,c});
                    }
                }
            }
        }
    }
    this->setNodeVisited(l,true);
    return listOfNewLocs;
}

std::vector<loc> grid::getAllActiveUnfinalized(){  // Using STL Vector Instead

    std::cout<<"Inside getAllActiveUnfinalized Method\n";
    std::vector<loc> list;
    for(int rowz = 0; rowz < g.rows(); rowz++){
        for(int colz = 0; colz < g.cols(); colz++){ /////COLZ! NOT ROWZ!
            //std::cout<<"we're in\n";
            if((this->getNodeVisited({rowz,colz}) == false) /*has not been visited Must set all obstacle 1's to Visited!!!*/ && (this->getNodeDistance({rowz,colz}) != -1) /*dist not -1*/){
                list.push_back({rowz,colz});
            }
            //std::cout<<"we're out\n";
        }
    }
    return list;
}

// End *important* methods

// the last 8 methods in grid.cpp are setter and getter methods to modify the lowest level stuff.

node grid::getNode(loc l){
    return g(l.row,l.col);
}

void grid::setNodeValue(loc l,int v){
    g(l.row,l.col).value = v;
}

int grid::getNodeValue(loc l){
    return g(l.row,l.col).value;
}

void grid::setNodeDistance(loc l,double d){
    g(l.row,l.col).distance = d;
}

double grid::getNodeDistance(loc l){
    return g(l.row,l.col).distance;
}

void grid::setNodeVisited(loc l,bool b){
    g(l.row,l.col).visited = b;
}

bool grid::getNodeVisited(loc l){
    return g(l.row,l.col).visited;
}

//void grid::setNodePointerToPrev(loc current, loc additional_which_points_back){  /////////////////// Area of Concern.  Ref vs value could still be a problem.
//    //g(additional_which_points_back.row,additional_which_points_back.col).pointerToPrevious = &(this->getNode(current));
//}

//node* grid::getNodePointerToPrev(loc l){
//    return g(l.row,l.col).pointerToPrevious;
//}

/*              hacky methods                                    */
void grid::setNodeLocToPrevious(loc current, loc pointsBack){
    g(pointsBack.row,pointsBack.col).locOfPrevious = current;
}

loc grid::getWhereNodePoints(loc it){
    return g(it.row,it.col).locOfPrevious;
}
