#include "node.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <eigen3/Eigen/Eigen>

node::node()
{
    value = 0;
    distance = -1;
    visited = false;
    pointerToPrevious = NULL;
    //locOfPrevious.row = -1;
    //locOfPrevious.col = -1;

}
