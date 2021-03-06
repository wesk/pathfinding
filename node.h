#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <vector>

struct loc{
    int row;
    int col;
};

struct loc_heur{
    loc location;
    int heuristic;
};

//struct tempLoc_dist{
//    loc l;
//    int dist;
//};

class node
{
public:
    node();
    int value; // if occupied (1), empty (0), or part of the path (2)  start(3) end(4)
    double distance; // distance from start
    bool visited; // true when all possible routes tested
    node* pointerToPrevious;
    //loc locOfPrevious; //Inelegant Solution, not using pointers anymore. Must improve.
    //void yo();
    int heuristic;
};

#endif // NODE_H
