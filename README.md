pathfinding
===========

A * pathfinding algorithm over 2d binary occupancy grid
Generalized Voronoi Diagram (GVD) generator.

todo: 
* Improve GVD generation, plan paths over GVD for max efficiency
* runtime optimizations

Dependencies:
* [pangolin](https://github.com/stevenlovegrove/pangolin)
* [eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page)

Setup:
* mkdir build
* cd build
* cmake ..
* make
* ./compiledBinary nameOfImageFile.png

Instantiate a grid, set the start, goal, and obstacles. 
Instantiate a pathfinder, pass the grid into the pathfinder constructor.
call the findpath() method

The program may be run with or without a gui:

### GUI:
Image must have occupied border, else GVD will be inaccurate
Default config: Start is top left corner, Goal is bottom right. Both nodes must be unoccupied

### Console:
comment out Pangolin/openGL stuff
Manually configure grid
use print or printEverything to get console output.

## Current configuration code within main.cpp should be understandable.
