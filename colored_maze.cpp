//
// Created by ryousuke kaga on 2023/11/08.
//

#include <iostream>
#include "ColoredGrid.h"
#include "DistanceGrid.h"
#include "algorithms.h"

int main() {
    ColoredGrid grid(10, 10);
    wilson(grid);

    grid.start = grid.getCell(grid.rows / 2, grid.columns / 2);
    grid.setDistances(grid.start->distances());

    char* filename = "colorized.png";
    grid.toPng(filename, 10);
}