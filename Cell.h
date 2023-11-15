//
// Created by ryousuke kaga on 2023/11/05.
//

#ifndef MAZE_IN_CPP_CELL_H
#define MAZE_IN_CPP_CELL_H

#include <set>
#include <vector>
#include <deque>
#include "Distances.h"

class Distances;

class Cell {
public:
    Cell(int row, int column);
    virtual Cell* link(Cell* cell, bool bidi=true);
    virtual Cell* unlink(Cell* cell, bool bidi=true);
    virtual bool linked(Cell* cell);
    Distances* distances();
    virtual std::vector<Cell*> neighbors();
    std::set<Cell*> links;
    Cell* north;
    Cell* south;
    Cell* east;
    Cell* west;
    int row;
    int column;
};


#endif //MAZE_IN_CPP_CELL_H
