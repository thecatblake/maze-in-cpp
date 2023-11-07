//
// Created by ryousuke kaga on 2023/11/05.
//

#include <iostream>
#include "Grid.h"
#include "algorithms.h"


int main() {
    Grid grid(30, 30);
    binary_tree(grid);

    char* file_name = "binary_tree_maze.png";

    grid.toPng(file_name, 10);

    std::cout << grid.toString() << std::endl;
}