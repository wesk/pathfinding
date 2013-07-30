#ifndef GRID_H
#define GRID_H
#include "node.h"
#include <eigen3/Eigen/Eigen>

// .block( , , , ) is not foolproof. It throws errors if it reaches out of range. If statements necessary

class grid{
protected:
    Eigen::Matrix<node,Eigen::Dynamic,Eigen::Dynamic> g;
    loc start;
    loc goal;

public:
    grid(int numRows, int numCols);
    void fill(int rowstart, int colstart, int rowlen, int collen);
    void clear(int rowstart, int colstart, int rowlen, int collen);
    void setStart(loc l);
    void setGoal(loc l);
    loc getStart();
    loc getGoal();
    void testConfig();
    void print();
    void printEverything();
    void outOfBound(loc amIOutOfRange); // returns to ensure input is legal.
    node* getAddressOfNode(loc l);
    bool areAdjacent(loc a, loc b);
    double calcDist(loc a, loc b);
    std::vector<loc> calcDistOfAllValidAdj(loc l);
    std::vector<loc> getAllActiveUnfinalized();
    void setNodeValue(loc l, int v);
    void setNodeDistance(loc l, double d);
    void setNodeVisited(loc l, bool b);
    int getNodeValue(loc l);
    double getNodeDistance(loc l);
    bool getNodeVisited(loc l);
    void setNodePointerToPrev(loc current, loc additional_which_points_back);
    void setNodeLocToPrevious(loc current, loc pointsBack);
    int calcManhattanHeuristic(loc l);

};

#endif // GRID_H
