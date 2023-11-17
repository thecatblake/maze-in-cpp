//
// Created by ryousuke kaga on 2023/11/15.
//

#include "PolarGrid.h"
#include "algorithms.h"

int main() {
    PolarGrid grid(20);
    recursive_backtracker(grid);

    grid.show(20);
}