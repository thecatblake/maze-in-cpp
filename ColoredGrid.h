//
// Created by ryousuke kaga on 2023/11/08.
//

#ifndef MAZE_IN_CPP_COLOREDGRID_H
#define MAZE_IN_CPP_COLOREDGRID_H

#include "Grid.h"

class ColoredGrid : public Grid {
public:
    ColoredGrid(int rows, int columns): Grid(rows, columns) {}
    std::tuple<int, int, int> backgroundColorFor(Cell *cell) override;
    void setDistances(Distances* distances);
    Distances* distances;
private:
    Cell* farthest;
    int maximum;
};


#endif //MAZE_IN_CPP_COLOREDGRID_H
