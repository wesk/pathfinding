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

//bool pathfinder::findClosest(loc_heur i, loc_heur j){
//    return( (i.heuristic) > (j.heuristic));
//}

int pathfinder::findMin(std::vector<loc_heur> it){
    int min = 0;
    for(unsigned int i = 1; i < it.capacity(); i++){
//        if(it[i].heuristic < it[min].heuristic){
//            min = i;
//        }
        if(it[i].heuristic + gr.getNodeDistance(it[i].location) <
                (it[min].heuristic + gr.getNodeDistance(it[min].location))){
            min = i;
        }
    }
    return min;
}

bool pathfinder::findPath(){

    std::vector<loc_heur> Master;
    std::vector<loc_heur> Secondary;
    std::cout<<"inside findpath method\n";
    Master = gr.calcDistOfAllValidAdj(gr.getStart());

    //int unsigned index = 0;
    int current = 0;
    while((gr.getNodeVisited(gr.getGoal()) == false)) /*&&
           Master.capacity() != 0)*/              {

        current = findMin(Master); //heuristic findmin
        Secondary = gr.calcDistOfAllValidAdj(Master[current].location);
        Master.erase(Master.begin()+current); // erase first term
        Master.insert(Master.end(), Secondary.begin(), Secondary.end());
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
