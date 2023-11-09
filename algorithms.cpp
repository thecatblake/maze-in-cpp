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

Grid& sidewinder(Grid& grid) {
    std::random_device r;
    std::default_random_engine generator(r());
    std::uniform_int_distribution<int> dist(0, (int)grid.cells.size());
    std::vector<Cell*> run;
    for(auto & cell : grid.cells) {
        run.push_back(cell);
        bool at_eastern_boundary = cell->east == nullptr;
        bool at_northern_boundary = cell->north == nullptr;
        bool should_close_out = at_eastern_boundary || (!at_northern_boundary && dist(generator) % 2 == 0);

        if (should_close_out) {
            Cell* member = run[dist(generator) % run.size()];
            if (member->north) member->link(member->north);
            run.erase(run.begin(), run.end());
        } else {
            cell->link(cell->east);
        }
    }

    return grid;
}

Grid& aldous_border(Grid& grid) {
    std::random_device r;
    std::default_random_engine generator(r());
    std::uniform_int_distribution<int> dist(0, 3);

    auto cell = grid.randomCell();
    int unvisited = (int)grid.cells.size() - 1;

    while (unvisited > 0) {
        auto neighbors = cell->neighbors();
        auto neighbor = neighbors[dist(generator) % neighbors.size()];

        if(neighbor && neighbor->links.empty()) {
            cell->link(neighbor);
            unvisited--;
        }

        cell = neighbor;
    }

    return grid;
}

Grid& wilson(Grid& grid) {
    std::random_device r;
    std::default_random_engine generator(r());
    std::uniform_int_distribution<int> dist(0, (int)grid.cells.size() - 1);
    std::vector<Cell*> unvisited;
    unvisited.reserve(grid.cells.size());

    for(auto & cell : grid.cells) {
        unvisited.push_back(cell);
    }

    auto first = unvisited[dist(generator) % (int)unvisited.size()];
    unvisited.erase(std::remove(unvisited.begin(), unvisited.end(), first), unvisited.end());

    while(!unvisited.empty()) {
        auto cell = unvisited[dist(generator) % (int)unvisited.size()];
        std::vector<Cell*> path = {cell};

        while(std::find(unvisited.begin(), unvisited.end(), cell) != unvisited.end()) {
            auto neighbors = cell->neighbors();
            cell = neighbors[dist(generator) % (int)neighbors.size()];
            auto position = std::find(path.begin(), path.end(), cell);

            if(position != path.end()) {
                path.erase(position, path.end());
            } else {
                path.push_back(cell);
            }
        }

        for(int i=0; i < path.size() - 1; i++) {
            path[i]->link(path[i + 1]);
            unvisited.erase(std::remove(unvisited.begin(), unvisited.end(), path[i]), unvisited.end());
        }
    }

    return grid;
}