cmake_minimum_required(VERSION 2.8)
project(pathfinding)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wextra -Wall")

# Find Pangolin (https://github.com/stevenlovegrove/Pangolin)
# find_package(Pangolin 0.1 REQUIRED)
# include_directories(${Pangolin_INCLUDE_DIRS})
# link_libraries(${Pangolin_LIBRARIES})

add_executable(compiledBinary main.cpp graph.cpp graph.h node.cpp node.h pathfinder.cpp pathfinder.h)
