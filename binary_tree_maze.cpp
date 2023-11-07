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
    grid.distances = grid.cells[0]->distances();

    char* file_name = "binary_tree_maze.png";

    grid.toPng(file_name, 10);

    std::cout << grid.toString() << std::endl;
}