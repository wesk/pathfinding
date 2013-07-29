#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <eigen3/Eigen/Eigen>
#include "grid.h"
#include "node.h"
#include "pathfinder.h"

int main(){

    grid g(40,40);
    g.fill(0,0,40,40);
    g.clear(1,1,38,38);
    g.setStart({3,3});
    g.setGoal({30,35});
//    g.fill(4,0,1,35);
//    g.fill(10,4,1,36);
//    g.fill(15,0,1,35);
//    g.fill(20,4,1,36);
//    g.fill(25,0,1,35);
//    g.fill(15,16,4,2);
//    g.fill(17,12,4,2);
//    g.fill(20,15,4,2);
    g.print();

    pathfinder p(g);
    if(!p.findPath()){
        p.getSolved().printEverything();
        std::cout<<"No Path Found                  No Path Found                           No Path Found                                No Path Found\n";
    }
    else{
        p.getSolved().printEverything();
    }
    return 1;
}
