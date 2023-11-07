//
// Created by ryousuke kaga on 2023/11/08.
//

#ifndef MAZE_IN_CPP_DISTANCES_H
#define MAZE_IN_CPP_DISTANCES_H

#include <unordered_map>
#include "Cell.h"

class Cell;

class Distances {
public:
    Distances(Cell* cell);
    int& operator[](Cell* cell);
    bool calculated(Cell* cell);
    Distances* pathTo(Cell* cell);
    std::unordered_map<Cell*, int> cells;
private:
    Cell* root;
};



#endif //MAZE_IN_CPP_DISTANCES_H
