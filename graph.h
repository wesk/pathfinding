#ifndef GRAPH_H
#define GRAPH_H
#include "node.h"


struct loc{
    int row;
    int col;
};


class graph{
protected:
    node g[50][50]; //todo: use dynamic std::vector instead // DOIN NOW!
    loc start;
    loc goal;

public:
    graph();
    void fill(int rowstart, int colstart, int rowlen, int collen);
    void clear(int rowstart, int colstart, int rowlen, int collen);
    void print(); // convert from int to pretty ascii pictures

    void setStart(int row, int col);
    void setGoal(int row, int col);
    node getAllAdjacentTo(loc l);

    node getNode(int row, int col);
    node getStart();
    node getGoal();

private:

    bool outOfBound(int amIOutOfRange); // returns to ensure input is legal.

};

#endif // GRAPH_H
