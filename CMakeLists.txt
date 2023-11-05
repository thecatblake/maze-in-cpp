cmake_minimum_required(VERSION 3.26)
project(maze_in_cpp)

set(CMAKE_CXX_STANDARD 17)

add_library(maze
        Grid.cpp
        Grid.h
        Cell.cpp
        Cell.h
        algorithms.cpp
        algorithms.h
)

add_executable(binary_tree_maze binary_tree_maze.cpp)
target_link_libraries(binary_tree_maze maze)
