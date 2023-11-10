//
// Created by ryousuke kaga on 2023/11/10.
//

#include <iostream>
#include "Grid.h"
#include "ColoredGrid.h"
#include "algorithms.h"


int main() {
    ColoredGrid grid(30, 30);
    binary_tree(grid);

    grid.start = grid.getCell(0, 0);
    grid.distances = grid.start->distances();
    auto [m_c, distance] = grid.distances->max();

    grid.setDistances(grid.distances->pathTo(m_c));

    grid.toPng("binary_tree_longest_path.png", 10);
}