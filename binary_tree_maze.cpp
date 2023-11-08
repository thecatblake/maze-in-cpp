//
// Created by ryousuke kaga on 2023/11/05.
//

#include <iostream>
#include "Grid.h"
#include "DistanceGrid.h"
#include "algorithms.h"


int main() {
    DistanceGrid grid(10, 10);
    binary_tree(grid);

    char* file_name = "binary_tree_maze.png";

    grid.toPng(file_name, 10);

    grid.start = grid.getCell(0, 0);
    grid.distances = grid.start->distances();
    auto [new_start, distance] = grid.distances->max();

    auto new_distance = new_start->distances();
    grid.distances = new_distance->pathTo(grid.start);

    std::cout << grid.toString() << std::endl;
}