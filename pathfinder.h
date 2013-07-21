#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "grid.h"
#include "node.h"

#ifndef PATHFINDER_H
#define PATHFINDER_H

class pathfinder
{
private:
    grid gr;
    int a = 120;
public:
    pathfinder(grid &gr);
    bool findPath();
    grid getSolved();
    void modifyTest();


private:
//    void calcDistOfAllAdj(loc l); //then, sets node as visited.
//    Eigen::Matrix<loc,Eigen::Dynamic,1> getAllActive_Unfinalized(); // returns vector of locs of nodes. each has distance != 1 && visited = false
    void updateGraph();
};

#endif // PATHFINDER_H
