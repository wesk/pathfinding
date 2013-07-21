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

bool pathfinder::findPath(){ // The Core. Dijkstra


    gr.calcDistOfAllValidAdj(gr.getStart());

    std::vector<loc> theMasterList;
    //theMasterList= gr.getAllActiveUnfinalized();

    std::cout<<"inside findpath method\n";
    do{
        theMasterList= gr.getAllActiveUnfinalized();
        std::cout<<"main loop running\n";
        for(unsigned int index = 0; index < theMasterList.capacity(); index ++){
            gr.calcDistOfAllValidAdj(theMasterList[index]);
        }
    }
    while(theMasterList.capacity() != 0);

    if(gr.getNodeVisited(gr.getGoal()) == true){
        updateGraph();
        return true;
    }
    return false;
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
