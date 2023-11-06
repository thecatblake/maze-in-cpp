//
// Created by ryousuke kaga on 2023/11/07.
//

#include <iostream>
#include "Grid.h"
#include "algorithms.h"


int main() {
    Grid grid(30, 30);
    binary_tree(grid);

    std::cout << grid.toString() << std::endl;
}