cmake_minimum_required(VERSION 3.26)
project(maze_in_cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_library(maze
        Grid.cpp
        Grid.h
        Cell.cpp
        Cell.h
        algorithms.cpp
        algorithms.h
        Distances.cpp
        Distances.h
        DistanceGrid.cpp
        DistanceGrid.h
)
target_link_libraries(maze libpng.a)
add_executable(binary_tree_maze binary_tree_maze.cpp)
target_link_libraries(binary_tree_maze maze)
add_executable(sidewinder_maze sidewinder_maze.cpp)
target_link_libraries(sidewinder_maze maze)