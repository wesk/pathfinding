#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "grid.h"
#include <algorithm>
#include "node.h"
#include "pathfinder.h"
pathfinder::pathfinder(grid &g) : gr(g) //Initialization Lists! Did not know this was needed.
{

}

bool pathfinder::findPath(){

    std::vector<loc> theMasterList;
    std::vector<loc> theSecondaryList;
    //theMasterList= gr.getAllActiveUnfinalized();
    std::cout<<"inside findpath method\n";
    theMasterList = gr.calcDistOfAllValidAdj(gr.getStart());

    //int unsigned index = 0;
    while((gr.getNodeVisited(gr.getGoal()) == false && theMasterList.capacity() != 0)/* || theMasterList.capacity() != 0*/){

        //this is the sort
        //dstarHeuristicSort(theMasterList);
        theSecondaryList = gr.calcDistOfAllValidAdj(theMasterList[0]);
        theMasterList.erase(theMasterList.begin()); // erase first term
        theMasterList.insert(theMasterList.end(), theSecondaryList.begin(), theSecondaryList.end());
        std::sort(theMasterList.begin(),theMasterList.end(),true);

    }

    std::cout<<"Main findPath loop exiting\n";
    if(gr.getNodeVisited(gr.getGoal()) == true){
        std::cout<<"Goal Visited!\n";
    }
    else{
        std::cout<<"goal NOT visited\n";
    }

    if(gr.getNodeVisited(gr.getGoal()) == true){
        updateGraph();
        return true;
    }
    else{
        std::cout<<"Grid Not Solved\n";
        return false;
    }
}

bool pathfinder::returnTrue(){
    return false;
}

///////////////// Astar
bool pathfinder::manhattanHeuristic(loc i, loc j){ //manhattan distance
    //loc goal = gr.getGoal();
//    loc goal;
//    goal.row = 100;
//    goal.col = 100;

//    return ((abs(goal.row - i.row) + abs(goal.col - i.col)) > (abs(goal.row - j.row) + abs(goal.col - j.col)));
    return true;
}

//void pathfinder::dstarHeuristicSort(std::vector<loc> &list){
//    std::sort(list.begin(),list.end(),pathfinder::manhattanHeuristic);
//    //std::vector<loc> sorted =  std::sort(list.begin(),list.end(),pathfinder::manhattanHeuristic);
//}
/////////////end astar

void pathfinder::updateGraph(){ // This steps backwards to the start, folowing the winning path.

    node* current = gr.getAddressOfNode(gr.getGoal());
    current = current->pointerToPrevious; // to avoid overwriting the goal (4) value
    while(current != gr.getAddressOfNode(gr.getStart())){ // same as above, for start(3)
        current->value = 2;
        current = current->pointerToPrevious;
    }
}

grid pathfinder::getSolved(){
    return gr;
}
