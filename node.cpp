#include "node.h"
#include <stdlib.h>


node::node()
{
    value = 0;
    distance = -1;
    visited = false;
    pointerToPrevious = NULL;

}
