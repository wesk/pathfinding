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

}

//void node::yo(){
//    std::cout<<"yo"<<std::endl;
//}
