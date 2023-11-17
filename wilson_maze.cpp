//
// Created by ryousuke kaga on 2023/11/09.
//
#include <iostream>
#include "Grid.h"
#include "ColoredGrid.h"
#include "algorithms.h"


int main() {
    Grid grid(30, 30);
    wilson(grid);

    grid.toPng("wilson_maze.png", 10);

    std::cout << grid.toString() << std::endl;

    ColoredGrid c_grid(30, 30);
    wilson(c_grid);
    c_grid.start = c_grid.getCell(c_grid.rows / 2, c_grid.columns / 2);
    c_grid.setDistances(c_grid.start->distances());

    c_grid.toPng("wilson_colored_maze.png", 10);

    ColoredGrid s_grid(30, 30);
    wilson(s_grid);
    s_grid.start = s_grid.getCell(0, 0);
    s_grid.setDistances(s_grid.start->distances());
    s_grid.setDistances(s_grid.distances->pathTo(s_grid.getCell(s_grid.rows - 1, s_grid.columns - 1)));

    s_grid.toPng("wilson_shortest_path.png", 10);

    s_grid.show(20);
}