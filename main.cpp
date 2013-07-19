#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <math.h>


#include "graph.h"
#include "node.h"

// ROW, then COLUMN notation.

//struct loc{
//    int row;
//    int col;
//};

int main(){

    std::vector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    std::vector<int>::iterator aIt;

    std::cout<<a.size()<<std::endl;

    for(aIt = a.begin(); aIt != a.end(); aIt++){ //careful reverse syntax
       std::cout<<*aIt<<std::endl;
    }

    //std::vector<std::vector<node>> p(2); // 2d vector of vectors

    std::vector <std::vector<int>> myvector(2);
    int qq[] = {0, 1, 2, 3, 4};
    size_t elements = sizeof(qq) / sizeof(int);

    myvector[0].reserve(elements);
    std::copy ( qq, qq + elements, std::back_inserter ( myvector[0] ) );


}
// std::cout<<(sizeof(a) / sizeof(node))<<" and "<<2500 <<std::endl;

/*  ~~~~~~~~~~~~~~~~yay linked lists!~~~~~~~~~~~~~~~~~~~~~
    node n1;
    n1.distance = 1;
    n1.pointerToPrevious = NULL; // careful w/ = vs ==

    node n2;
    n2.distance = 2;
    node n3;
    n3.distance = 3;
    n3.pointerToPrevious = &n2;
    n2.pointerToPrevious = &n1;


    node n4;
    n4.distance = 4;
    n4.pointerToPrevious = &n3;

    node* index = &n4;
    while(index != NULL){
        std::cout<<index->distance<<std::endl;
        index = index->pointerToPrevious;
    }
*/
