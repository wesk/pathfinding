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
    //int a = 120;
public:
    pathfinder(grid& gr);
    bool findPath();
    grid getSolved();
    void modifyTest();

    static bool findClosest(loc_heur i, loc_heur j);
    int findMin(std::vector<loc_heur> it);
    //void dstarHeuristicSort(std::vector<loc> &list);
    //static bool manhattanHeuristic(const loc &i, const loc &j);
    //int manhattanDist(loc l);
    //bool returnTrue();
    //void personalSortingAlgorithm(std::vector<loc> &l);

private:
    void updateGraph();
};

#endif // PATHFINDER_H
