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

void grid::fillSingle(const int& r, const int& c){
    g(r,c).value = 1;
    g(r,c).visited = true;
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

void grid::outOfBound(const loc& amIOutOfRange){

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
//            else if(present == 2){
//                std::cout<<(char)0x40<<" ";
//            }
            else{
                std::cout<<present<<" ";
            }
        }
        std::cout<<"\n";
    }
}

void grid::printNiceSpacing(){
    for(int i = 0; i < g.rows(); i++){
        for(int j = 0; j < g.cols(); j++){
            int present = g(i,j).value;
            if(present == 0){
                std::cout<<"  ";
            }
//            else if(present == 2){
//                std::cout<<(char)0x40<<" ";
//            }
            else{
                std::cout<<std::setw(2)<<present<<" ";
            }
        }
        std::cout<<"\n";
    }
    std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

void grid::printEverything(){

    std::cout<<"~~~~~~~~~~~~~~~~~~~distance~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    for(int i = 0; i < g.rows(); i++){
        for(int j = 0; j < g.cols(); j++){
            double present = g(i,j).distance;
            std::cout<<std::setw(2)<< present;

        }
        std::cout<<("\n");

    }
//    std::cout<<"~~~~~~~~~~~~~~~~~visited~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
//    for(int i = 0; i < g.rows(); i++){
//        for(int j = 0; j < g.cols(); j++){
//            bool present = g(i,j).visited;
//            std::cout<<present<<" ";
//        }
//        std::cout<<"\n";
//    }

//    std::cout<<"~~~~~~~~~~~~~~~~~address of previous~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
//    for(int i = 0; i < g.rows(); i++){
//        for(int j = 0; j < g.cols(); j++){
//            node* present = g(i,j).pointerToPrevious;
//            std::cout<<std::setw(8)<<present<<" ";
//        }
//        std::cout<<"\n";
//        std::cout<<"\n";
//    }
//    std::cout<<"~~~~~~~~~~~~~~~~~~~heuristic~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
//    for(int i = 0; i < g.rows(); i++){
//        for(int j = 0; j < g.cols(); j++){
//            std::cout<<std::setw(3)<<g(i,j).heuristic;
//        }
//        std::cout<<"\n";
//    }
    std::cout<<"~~~~~~~~~~~~~~~~~~~~~value:~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    this->print();
}

// This returns a vector of locs, to pass to another function, instead of getAllActiveUnfinalized. This is the most important method.
std::vector<loc_heur> grid::calcDistOfAllValidAdj(loc l){
    outOfBound(l);
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

    std::vector<loc_heur> new_list;

    for(int r = rowstart; r <= rowend; r++){// <=, not just <
        for(int c = colstart; c <= colend; c++){
            if(!(g(r,c).value == 1)){// anything but 1. 1 means full.

                // if it hasn't been visited yet, this updates the new distance. Otherwise, see the else statement for distance check.
                if(g(r,c).distance == -1){
                    this->setNodeDistance({r,c},this->getNodeDistance(l)+this->calcDist(l,{r,c}));
                    this->setNodePointerToPrev(l,{r,c}); //pointer method

                    // adds the loc to the new list of where to still search
                    loc_heur current;
                    current.location = {r,c};
                    current.heuristic = getHeurist({r,c});
                    //current.p_heuristic =
                    new_list.push_back(current);

                    //listOfNewLocs.push_back({r,c});
                }
                else{ // If it has been visited, check to see if this way is shorter. if so, update  like the previous two lines. else, do nothing.
                    if(this->getNodeDistance({r,c}) > this->getNodeDistance(l)+this->calcDist(l,{r,c})){
                        this->setNodeDistance({r,c},this->getNodeDistance(l)+this->calcDist(l,{r,c}));
                        //this->setNodeLocToPrevious(l,{r,c});
                        this->setNodePointerToPrev(l,{r,c});
                    }
                }
            }
        }
    }
    this->setNodeVisited(l,true);
    return new_list;
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


//void grid::testConfig(){
//    std::cout<<"You have chosen the convenient testing constructor\n";
//    g.resize(10,10);
//    this->fill(0,0,10,10);
//    this->clear(1,1,8,8);
//    this->fill(0,2,5,1);
//    this->fill(0,3,5,1);
//    this->fill(3,5,7,1);
//    this->fill(3,6,7,1);
//    loc s {6,3};
//    loc gg {4,7};
//    this->setStart(s);
//    this->setGoal(gg);
//}

void grid::setStart(loc l){
    start = l;
    g(l.row,l.col).value = 3;
    this->setNodeDistance(l,0);

}

int grid::calcManhattanHeuristic(loc l){

    return abs(goal.row-l.row) + abs(goal.col-l.col);

}

void grid::setGoal(loc l){
    goal = l;
    g(l.row,l.col).value = 4;
    //set heuristic for all nodes in grid

    for(int r = 0; r < g.rows(); r++){
        for(int c = 0; c < g.cols(); c++){
            g(r,c).heuristic = calcManhattanHeuristic({r,c});
        }
    }
}
///////////////////// Brushfire/Voronoi Stuff
///
/*

brushfire copies the existing value, occupied (1) or empty (0) into node.distance
node.distance stores the distance of that node to the nearest obstruction

value then is filled with the wavefront collision. '5' shall be used, just because.


*/
std::vector<loc> grid::getAdjacentToLoc(loc l){
    outOfBound(l);
    std::vector<loc> adjLocs;
    int rowStart = l.row;
    int colStart = l.col;
    int rowEnd = l.row;
    int colEnd = l.col;
    if(!(l.row-1 < 0)){
        rowStart -= 1;
    }
    if(!(l.col-1 < 0)){
        colStart -= 1;
    }
    if(!(l.row+1 > g.rows()-1)){
        rowEnd += 1;
    }
    if(!(l.col+1 > g.cols()-1)){
        colEnd += 1;
    }
    for(int k = rowStart; k <= rowEnd; k++){
        for(int p = colStart; p <= colEnd; p++){
            if (!(l.row == k && l.col == p)){
                loc current;
                current.row = k;
                current.col = p;
                if(!(current.col == 0 && current.row == 0)){
                    adjLocs.push_back(current);
                }

            }
        }
    }
    return adjLocs;
}

std::vector<loc> grid::getManhattanAdjacentToLoc(loc l){
    outOfBound(l);
    std::vector<loc> adjLocs;
    int rowStart = l.row;
    int colStart = l.col;
    int rowEnd = l.row;
    int colEnd = l.col;
    if(!(l.row-1 < 0)){
        rowStart -= 1;
    }
    if(!(l.col-1 < 0)){
        colStart -= 1;
    }
    if(!(l.row+1 > g.rows()-1)){
        rowEnd += 1;
    }
    if(!(l.col+1 > g.cols()-1)){
        colEnd += 1;
    }
    for(int k = rowStart; k <= rowEnd; k++){
        for(int p = colStart; p <= colEnd; p++){
            if (!(l.row == k && l.col == p)){ //not same as loc  l
                if(calcDist(l,{k,p}) == 1){ //if it is orthogonal
                    loc current;
                    current.row = k;
                    current.col = p;
                    adjLocs.push_back(current);
                }
            }
        }
    }
    return adjLocs;
}

void grid::genBrushfire(){ // modifying node.distance, not node.value

    //set node.distance to be the same as node.value in all cases
    for(int i = 0; i < g.rows(); i++){
        for(int j = 0; j < g.cols(); j++){
            g(i,j).distance = g(i,j).value;
        }
    }

    std::vector<loc> list;
    std::vector<loc>::iterator list_iterator;
    std::vector<tempLoc_dist> tempList;
    std::vector<tempLoc_dist>::iterator tempList_iterator;
    tempLoc_dist t; // element stored within tempList;
    bool done = false;
    while(!done){ //while the grid isn't entirely full
        for(int r = 0; r < g.rows(); r++){
            for(int c = 0; c< g.cols(); c++){ //iterate through entire grid
                if(getNodeDistance({r,c}) == 0){ // if r/c not occupied
                    list = getAdjacentToLoc({r,c}); // look for adj occupied nodes
                    list = getManhattanAdjacentToLoc({r,c});
                    for(list_iterator = list.begin(); list_iterator != list.end(); list_iterator++){
                        if(!(getNodeDistance(*list_iterator) == 0)){ //when one is found
                            t.l = {r,c};
                            t.dist = getNodeDistance(*list_iterator)+1; //1+ than prev
                            tempList.push_back(t);
                        }
                    }
                }
            }
        }
        //now, update grid with new data.
        for(tempList_iterator = tempList.begin(); tempList_iterator != tempList.end(); tempList_iterator++){
            if(getNodeDistance(tempList_iterator->l) == 0){
                setNodeDistance(tempList_iterator->l, tempList_iterator->dist);
            }
            else{
                //setNodeValue(tempList_iterator->l,5);
            }
            //here is where we need to look for duplicates
        }
        //checks for end case
        bool zero = false;
        for(int i = 0; i < g.rows(); i++){
            for(int j = 0; j < g.cols(); j++){
                if(g(i,j).distance == 0){
                    zero = true;
                }
            }
        }
        if(!zero){
            done = true;
        }
    }
    printEverything();
}

void grid::genVoronoi(){
    std::vector<loc> adj;
    std::vector<loc>::iterator loc_iterator;
    int currDist;
    bool candidate;
    for(int r = 0; r < g.rows(); r++){
        for(int c = 0; c < g.cols(); c++){
            if(getNodeValue({r,c}) != 1){ //not occupied
                candidate = true;
                adj = getManhattanAdjacentToLoc({r,c});
                currDist = getNodeDistance({r,c});
                //if there are any orthogonally adjacent nodes with a higher distance,
                //the current node is not on the voronoi wave collision
                for(loc_iterator = adj.begin(); loc_iterator != adj.end(); loc_iterator++){
                    if(currDist < getNodeDistance(*loc_iterator)){
                        candidate = false;
                    }
                }
                if(candidate){
                    setNodeValue({r,c},5);
                }
            }
        }
    }
}

////////////////END Brushfire/Voronoi
///

loc grid::getStart(){
    return start;
}

loc grid::getGoal(){
    return goal;
}

node* grid::getAddressOfNode(loc l){
    return &g(l.row,l.col);
}

int grid::getHeurist(loc l){
    return g(l.row,l.col).heuristic;
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

void grid::setNodePointerToPrev(loc current, loc additional_which_points_back){  /////////////////// Area of Concern.  Ref vs value could still be a problem.
    g(additional_which_points_back.row,additional_which_points_back.col).pointerToPrevious = this->getAddressOfNode(current);
}
