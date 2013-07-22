#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <eigen3/Eigen/Eigen>
#include "grid.h"
#include "node.h"
#include "pathfinder.h"


int main(){


    //grid myG(20,20);
    //myG.fill(0,0,20,20);
    //myG.clear(1,1,18,18);
    //myG.fill(11,2,1,10);
    //myG.fill(6,8,5,1);
    //myG.setGoal({12,7});
    //myG.setStart({6,6});
    grid myG(10,10);
    myG.testConfig();
    myG.fill(4,4,1,1);
    myG.printEverything();

    pathfinder finder(myG);

    if(!finder.findPath()){
        finder.getSolved().printEverything();
        std::cout<<"No Path Found                  No Path Found                           No Path Found                                No Path Found\n";
    }
    else{
        finder.getSolved().printEverything();
    }



    return 1;
}



















// IF have no parameter constructor, Don't Use Parenthesis ()()()()
// Eigen: Use Blocks to access portions.  .block(, , , , ,)
//no syntax suggestions? HmmMmMm
//use fixed size blocks

// std::cout<<(sizeof(a) / sizeof(node))<<" and "<<2500 <<std::endl; array size memory manipulations.

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
//    std::vector<int> a;
//    a.push_back(1);
//    a.push_back(2);
//    a.push_back(3);
//    a.push_back(4);
//    std::vector<int>::iterator aIt;

//    std::cout<<a.size()<<std::endl;

//    for(aIt = a.begin(); aIt != a.end(); aIt++){ //careful reverse syntax
//       std::cout<<*aIt<<std::endl;
//    }

//    //std::vector<std::vector<node>> p(2); // 2d vector of vectors

//    std::vector <std::vector<int>> myvector(2);
//    int qq[] = {0, 1, 2, 3, 4};
//    size_t elements = sizeof(qq) / sizeof(int);

//    myvector[0].reserve(elements);
//    std::copy ( qq, qq + elements, std::back_inserter ( myvector[0] ) );

//~~~~~~~~~~~~~~~``

/*  ///// BLA Experimentation Stuff
 *
    Eigen::MatrixXd m = Eigen::MatrixXd::Random(3,3); //capital R, no auto
    std::cout<<m<<std::endl;

    Eigen::Matrix<node,Eigen::Dynamic,Eigen::Dynamic> map;
    map.resize(10,10);
    map(0,0).value = 1;


    // normal print doesn't work. Frown.
    for(int i = 0; i < map.rows(); i++){
        for(int j = 0; j < map.cols(); j++){
            map(i,j).value = i*j;
            std::cout<<map(i,j).value<<" ";
        }
        std::cout<<"\n";
    }

    Eigen::Matrix<node,3,3> chunk = map.block(8,8,3,3);

    for(int i = 0; i < chunk.rows(); i++){
        for(int j = 0; j < chunk.cols(); j++){
            std::cout<<chunk(i,j).value<<" ";
        }
        std::cout<<"\n";
    }
*/

/*
     Eigen::Matrix<int,Eigen::Dynamic,Eigen::Dynamic> g;
     g.resize(5,5);
     g(2,2) = 1;
     g(2,3) = 1;
     g(3,2) = 1;
     g(3,3) = 1;

     Eigen::Matrix<int,Eigen::Dynamic,Eigen::Dynamic> a;
     a.resize(2,2);
     a(0,0) = 9;
     a(1,0) = 9;
     a(0,1) = 9;
     a(1,1) = 9;

     g.block(3,3,2,2) = a;

    std::cout<<g<<"\n"<<a<<std::endl;

*/
