#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "grid.h"
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

    int unsigned index = 0;
    while((gr.getNodeVisited(gr.getGoal()) == false && index < theMasterList.capacity())/* || theMasterList.capacity() != 0*/){

        //std::cout<<"main loop running\n";

        theSecondaryList = gr.calcDistOfAllValidAdj(theMasterList[index]);
        theMasterList.insert(theMasterList.end(), theSecondaryList.begin(), theSecondaryList.end());

        index ++;

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
        std::cout<<"Graph Not Solved\n";
        return false;
    }
}

void pathfinder::updateGraph(){ // This steps backwards to the start, folowing the winning path.
    loc current = gr.getWhereNodePoints(gr.getGoal());
    loc start = gr.getStart();
    while(!(current.row == start.row && current.col == start.col)){ //while the current loc is not the start loc
        gr.setNodeValue(current,2);
        current = gr.getWhereNodePoints(current);
    }
}

grid pathfinder::getSolved(){
    return gr;
}
