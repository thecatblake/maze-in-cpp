//
// Created by ryousuke kaga on 2023/11/11.
//

#include <iostream>
#include "Grid.h"
#include "MaskGrid.h"
#include "algorithms.h"

int main() {
    Mask mask(5, 5);

    *mask(0, 0) = false;
    *mask(2, 2) = false;
    *mask(4, 4) = false;

    std::cout << mask.bits[1] << std::endl;

    MaskGrid grid(&mask);
    recursive_backtracker(grid);

    std::cout << grid.toString() << std::endl;
}