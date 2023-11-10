//
// Created by ryousuke kaga on 2023/11/10.
//

#include <iostream>
#include "Grid.h"
#include "ColoredGrid.h"
#include "algorithms.h"


int main() {
    Grid grid(30, 30);
    recursive_backtracker(grid);

    grid.toPng("recursive_backtracker_maze.png", 10);

    std::cout << grid.toString() << std::endl;

    ColoredGrid c_grid(30, 30);
    recursive_backtracker(c_grid);
    c_grid.start = c_grid.getCell(c_grid.rows / 2, c_grid.columns / 2);
    c_grid.setDistances(c_grid.start->distances());

    c_grid.toPng("recursive_backtracker_colored_maze.png", 10);

    c_grid.start = c_grid.getCell(0, 0);
    c_grid.setDistances(c_grid.start->distances());
    c_grid.setDistances(c_grid.distances->pathTo(c_grid.getCell(c_grid.rows - 1, c_grid.columns - 1)));

    c_grid.toPng("recursive_backtracker_shortest_path.png", 10);

    c_grid.start = c_grid.getCell(0, 0);
    c_grid.distances = c_grid.start->distances();
    auto [m_c, distance] = c_grid.distances->max();

    c_grid.setDistances(c_grid.distances->pathTo(m_c));

    c_grid.toPng("recursive_backtracker_longest_path.png", 10);
}