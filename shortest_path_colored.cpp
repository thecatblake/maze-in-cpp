//
// Created by ryousuke kaga on 2023/11/09.
//

#include <iostream>
#include "ColoredGrid.h"
#include "DistanceGrid.h"
#include "algorithms.h"

int main() {
    ColoredGrid grid(50, 50);
    aldous_border(grid);
    grid.start = grid.getCell(0, 0);
    grid.setDistances(grid.start->distances());
    grid.setDistances(grid.distances->pathTo(grid.getCell(grid.rows - 1, grid.columns - 1)));

    char* filename = "shortest_colorized.png";
    grid.toPng(filename, 10);
}