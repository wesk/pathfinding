#ifndef GRAPH_H
#define GRAPH_H
#include "node.h"
#include <eigen3/Eigen/Eigen>

// .block( , , , ) is not foolproof. It throws errors if it reaches out of range. If statements necessary


struct loc{
    int row;
    int col;
};


class graph{
protected:
    Eigen::Matrix<node,Eigen::Dynamic,Eigen::Dynamic> g;
    loc start;
    loc goal;

public:
    graph(int numRows, int numCols);

    void fill(int rowstart, int colstart, int rowlen, int collen);
    void clear(int rowstart, int colstart, int rowlen, int collen);
    void setStart(loc l);
    void setGoal(loc l);

    Eigen::Matrix<node,Eigen::Dynamic,Eigen::Dynamic> getAllAdjacentTo(loc l);

    node getNode(int row, int col);
    node getStart();
    node getGoal();

    void testConfig();

    void print(); // TODO convert from int to pretty ascii pictures


private:

    void outOfBound(loc amIOutOfRange); // returns to ensure input is legal.

};

#endif // GRAPH_H
