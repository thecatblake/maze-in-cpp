cmake_minimum_required(VERSION 3.26)
project(maze_in_cpp)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)

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
        ColoredGrid.cpp
        ColoredGrid.h
        Mask.cpp
        Mask.h
        MaskGrid.cpp
        MaskGrid.h
        PolarGrid.cpp
        PolarGrid.h
        PolarCell.cpp
        PolarCell.h
        HexCell.cpp
        HexCell.h
        HexGrid.cpp
        HexGrid.h
)
target_link_libraries(maze libpng.a SDL2::SDL2)
add_executable(binary_tree_maze binary_tree_maze.cpp)
target_link_libraries(binary_tree_maze maze)
add_executable(sidewinder_maze sidewinder_maze.cpp)
target_link_libraries(sidewinder_maze maze)
add_executable(colored_maze colored_maze.cpp)
target_link_libraries(colored_maze maze)
add_executable(aldous_border_maze aldous_border_maze.cpp)
target_link_libraries(aldous_border_maze maze)
add_executable(shortest_path_colored shortest_path_colored.cpp)
target_link_libraries(shortest_path_colored maze)
add_executable(wilson_maze wilson_maze.cpp)
target_link_libraries(wilson_maze maze)
add_executable(hunt_and_kill_maze hunt_and_kill_maze.cpp)
target_link_libraries(hunt_and_kill_maze maze)
add_executable(deadend_counts deadend_counts.cpp)
target_link_libraries(deadend_counts maze)
add_executable(recursive_backtracker_maze recursive_backtracker_maze.cpp)
target_link_libraries(recursive_backtracker_maze maze)
add_executable(longest_path_colored longest_path_colored.cpp)
target_link_libraries(longest_path_colored maze)
add_executable(mask_maze mask_maze.cpp)
target_link_libraries(mask_maze maze)
add_executable(polar_grid_maze polar_grid_maze.cpp)
target_link_libraries(polar_grid_maze maze)
add_executable(hex_grid_maze hex_grid_maze.cpp)
target_link_libraries(hex_grid_maze maze)