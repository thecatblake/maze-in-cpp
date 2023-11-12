//
// Created by ryousuke kaga on 2023/11/11.
//

#include <iostream>
#include "Grid.h"
#include "MaskGrid.h"
#include "algorithms.h"

int main() {
    //auto mask = std::make_unique<Mask>(5, 5);
    //*(*mask)(0, 0) = false;
    //MaskGrid grid(mask);
    auto grid = MaskGrid::loadPng("/Users/ryousukekaga/repositories/maze-in-cpp/X_maze.png");

    recursive_backtracker(*grid);

    grid->toPng("mask_maze.png", 10);

    std::cout << grid->toString() << std::endl;
}