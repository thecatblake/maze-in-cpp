//
// Created by ryousuke kaga on 2023/11/05.
//

#include "algorithms.h"

Grid& binary_tree(Grid& grid) {
    std::random_device r;
    std::default_random_engine generator(r());
    std::uniform_int_distribution<int> dist(0, 1);

    for(auto & cell : grid.cells) {
        std::vector<Cell*> neighbors;

        if(cell->north)
            neighbors.push_back(cell->north);
        if(cell->east)
            neighbors.push_back(cell->east);

        if(neighbors.empty())
            continue;

        size_t index = dist(generator) % neighbors.size();
        cell->link(neighbors[index]);
    }

    return grid;
}