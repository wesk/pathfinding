#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "graph.h"
#include "node.h"

#ifndef PATHFINDER_H
#define PATHFINDER_H

class pathfinder
{
private:
    graph myG; // this is the one we will solve
public:
    pathfinder(graph g);
    bool findPath();
    graph getSolved();
private:

};

#endif // PATHFINDER_H
