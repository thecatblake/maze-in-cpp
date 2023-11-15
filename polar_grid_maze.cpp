//
// Created by ryousuke kaga on 2023/11/15.
//

#include "PolarGrid.h"
#include "algorithms.h"

int main() {
    PolarGrid grid(10);
    recursive_backtracker(grid);

    grid.setDistances(grid.cells[0][0]->distances());

    grid.toPng("polar_grid_maze.png", 100);
}