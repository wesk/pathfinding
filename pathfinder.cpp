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
