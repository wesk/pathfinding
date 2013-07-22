#ifndef NODE_H
#define NODE_H

struct loc{
    int row;
    int col;
};

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
};

#endif // NODE_H
