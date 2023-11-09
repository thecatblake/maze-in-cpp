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
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<Cell*> unvisited;
    unvisited.reserve(grid.cells.size());

    for(auto & cell : grid.cells) {
        unvisited.push_back(cell);
    }

    std::shuffle(unvisited.begin(), unvisited.end(), rd);
    auto first = unvisited[0];
    unvisited.erase(std::remove(unvisited.begin(), unvisited.end(), first), unvisited.end());

    while(!unvisited.empty()) {
        std::shuffle(unvisited.begin(), unvisited.end(), rd);
        auto cell = unvisited[0];
        std::vector<Cell*> path = {cell};

        while(std::find(unvisited.begin(), unvisited.end(), cell) != unvisited.end()) {
            auto neighbors = cell->neighbors();
            std::shuffle(neighbors.begin(), neighbors.end(), rd);
            cell = neighbors[0];
            auto position = std::find(path.begin(), path.end(), cell);

            if(position != path.end()) {
                path.erase(position+1, path.end());
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

Grid& hunt_and_kill(Grid& grid) {
    std::random_device rd;
    std::mt19937 g(rd());
    auto current = grid.randomCell();
    while (current) {
        auto neighbors = current->neighbors();
        std::vector<Cell*> unvisited_neighbors;

        for (auto & neighbor : neighbors) {
            if(neighbor->links.empty())
                unvisited_neighbors.push_back(neighbor);
        }

        if(!unvisited_neighbors.empty()) {
            std::shuffle(unvisited_neighbors.begin(), unvisited_neighbors.end(), g);
            auto neighbor = unvisited_neighbors[0];
            current->link(neighbor);
            current = neighbor;
        } else {
            current = nullptr;

            for (auto & cell : grid.cells) {
                std::vector<Cell*> visited_neighbors;

                for (auto & neighbor : cell->neighbors()) {
                    if(!neighbor->links.empty()) {
                        visited_neighbors.push_back(neighbor);
                    }
                }

                if(cell->links.empty() && !visited_neighbors.empty()) {
                    current = cell;
                    std::shuffle(visited_neighbors.begin(), visited_neighbors.end(), g);
                    auto neighbor = visited_neighbors[0];

                    current->link(neighbor);
                    break;
                }
            }
        }
    }

    return grid;
}