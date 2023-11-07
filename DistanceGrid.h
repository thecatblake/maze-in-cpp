//
// Created by ryousuke kaga on 2023/11/08.
//

#ifndef MAZE_IN_CPP_DISTANCEGRID_H
#define MAZE_IN_CPP_DISTANCEGRID_H

#include "Grid.h"

class DistanceGrid : public Grid {
public:
    DistanceGrid(int rows, int columns);
    std::string content_of(Cell* cell) override;
    Distances* distances;
private:
    std::unordered_map<int, std::string> b36;
};


#endif //MAZE_IN_CPP_DISTANCEGRID_H
