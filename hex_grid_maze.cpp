//
// Created by ryousuke kaga on 2023/11/22.
//


#include "HexGrid.h"
#include "algorithms.h"

int main() {
    HexGrid grid(20, 20);
    recursive_backtracker(grid);

    grid.show(20);
}