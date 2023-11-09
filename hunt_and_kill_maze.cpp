//
// Created by ryousuke kaga on 2023/11/10.
//


#include <iostream>
#include "Grid.h"
#include "ColoredGrid.h"
#include "algorithms.h"


int main() {
    Grid grid(30, 30);
    hunt_and_kill(grid);

    grid.toPng("hunt_and_kill_maze.png", 10);

    std::cout << grid.toString() << std::endl;

    ColoredGrid c_grid(30, 30);
    hunt_and_kill(c_grid);
    c_grid.start = c_grid.getCell(c_grid.rows / 2, c_grid.columns / 2);
    c_grid.setDistances(c_grid.start->distances());

    c_grid.toPng("hunt_and_kill_colored_maze.png", 10);

    ColoredGrid s_grid(30, 30);
    hunt_and_kill(s_grid);
    s_grid.start = s_grid.getCell(0, 0);
    s_grid.setDistances(s_grid.start->distances());
    s_grid.setDistances(s_grid.distances->pathTo(s_grid.getCell(s_grid.rows - 1, s_grid.columns - 1)));

    s_grid.toPng("hunt_and_kill_shortest_path.png", 10);
}