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

//    std::vector<loc> theMasterList;
//    std::vector<loc> theSecondaryList;
    list_heuristic Master;
    list_heuristic Secondary;
    std::cout<<"inside findpath method\n";
    Master = gr.calcDistOfAllValidAdj(gr.getStart());

    //int unsigned index = 0;
    while((gr.getNodeVisited(gr.getGoal()) == false &&
           Master.listOfLocs.capacity() != 0)){

        Secondary = gr.calcDistOfAllValidAdj(Master.listOfLocs[0]);
        Master.listOfLocs.erase(Master.listOfLocs.begin()); // erase first term
        Master.listOfLocs.insert(Master.listOfLocs.end(), Secondary.listOfLocs.begin(), Secondary.listOfLocs.end());
        //std::min ()
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



//void pathfinder::personalSortingAlgorithm(std::vector<loc> &l){
//    //selection sort
//    int current;
//    int smallest;
//    for(unsigned int i = 0; i < l.capacity(); i++){
//        current = i;
//        for(unsigned int j = i+1; j < l.capacity(); ++j){
//            if((manhattanDist(l[j]) < manhattanDist(l[current]))){
//                smallest = j;
//            }
//        }
//        int temp = current;
//        l[current] = l[smallest];
//        l[smallest] = l[temp];
//    }
//}


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
