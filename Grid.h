//
// Created by ryousuke kaga on 2023/11/05.
//

#ifndef MAZE_IN_CPP_GRID_H
#define MAZE_IN_CPP_GRID_H

#include <utility>
#include <random>
#include "Cell.h"

class Grid {
public:
    Grid(int rows, int columns);
    ~Grid();
    Cell* operator [](std::pair<int, int> index);
    Cell* getCell(int row, int column);
    Cell* randomCell();
    std::vector<Cell*> cells;
    std::string toString();
private:
    int rows;
    int columns;
    std::default_random_engine _generator;
    std::uniform_int_distribution<int> _dist;
};


#endif //MAZE_IN_CPP_GRID_H
