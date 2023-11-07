//
// Created by ryousuke kaga on 2023/11/07.
//

#include <iostream>
#include "Grid.h"
#include "algorithms.h"


int main() {
    Grid grid(30, 30);
    binary_tree(grid);

    char* file_name = "sidewinder_maze.png";

    grid.toPng(file_name, 10);

    std::cout << grid.toString() << std::endl;
}