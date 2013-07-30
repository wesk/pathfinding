pathfinding
===========

simple breadth-first search algorithm over 2d binary occupancy grid

Dependencies:
* [pangolin](https://github.com/stevenlovegrove/pangolin)
* [eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page)

Setup:
* mkdir build
* cd build
* cmake ..

Sample code within main.cpp should be fairly clear.

Instantiate a grid, set the start, goal, and obstacles. 
Instantiate a pathfinder, pass the grid into the pathfinder constructor.
call the findpath() method
