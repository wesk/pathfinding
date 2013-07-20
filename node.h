#ifndef NODE_H
#define NODE_H

class node
{
public:
    node();
    int value; // if occupied (1), empty (0), or part of the path (2)  start(3) end(4)
    int distance; // distance from start
    bool visited; // true when all possible routes tested
    struct node* pointerToPrevious;
    //void yo();
};

#endif // NODE_H
