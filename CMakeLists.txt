cmake_minimum_required(VERSION 2.8)
project(pathfinding)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wextra -Wall")

#Find Pangolin (https://github.com/stevenlovegrove/Pangolin)
find_package(Pangolin 0.1 REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})

add_executable(compiledBinary main.cpp grid.cpp grid.h node.cpp node.h pathfinder.cpp pathfinder.h)
target_link_libraries(compiledBinary ${Pangolin_LIBRARIES})

