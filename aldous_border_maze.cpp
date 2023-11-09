//
// Created by ryousuke kaga on 2023/11/09.
//
#include <iostream>
#include "Grid.h"
#include "algorithms.h"


int main() {
    Grid grid(30, 30);
    aldous_border(grid);

    char* file_name = "aldous_border_maze.png";

    grid.toPng(file_name, 10);

    std::cout << grid.toString() << std::endl;
}