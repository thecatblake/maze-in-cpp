//
// Created by ryousuke kaga on 2023/11/10.
//

#include "Grid.h"
#include "algorithms.h"
#include <iostream>

int main() {
    std::string f_names[] = {"binary_tree", "sidewinder", "Aldous border", "Wilson", "hunt-and-kill"};
    Grid& (* algorithms[])(Grid&) = {binary_tree, sidewinder, aldous_border, wilson, hunt_and_kill};

    int tries = 100;
    int size = 20;

    double averages[5];

    for(int i=0; i < 5; i++) {
        auto algorithm = algorithms[i];
        std::cout << "running " << f_names[i] << "..." << std::endl;

        std::vector<size_t> dead_counts;

        for(int j=0; j < tries; j++) {
            Grid grid(size, size);
            algorithm(grid);
            dead_counts.push_back(grid.deadends().size());
        }

        averages[i] = (double)std::reduce(dead_counts.begin(), dead_counts.end()) / (double)dead_counts.size();
    }

    for(int i=0; i < 5; i++) {
        std::cout << f_names[i] << ":\t" << averages[i] << "/" << size * size << "\t" << 100 * (int)averages[i] / (size*size) << "% (deadends/cells)" << std::endl;
    }
}