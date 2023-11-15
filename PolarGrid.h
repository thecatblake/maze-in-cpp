//
// Created by ryousuke kaga on 2023/11/15.
//

#ifndef MAZE_IN_CPP_POLARGRID_H
#define MAZE_IN_CPP_POLARGRID_H


#include "Grid.h"
#include "PolarCell.h"

class PolarGrid : public Grid {
public:
    PolarGrid(int rows);
    PolarCell* getCell(int row, int column);
    PolarCell* randomCell();
    std::vector<std::vector<PolarCell*>> cells;
    void toPng(char* file_name, int cell_size);
    int rows;
    PolarCell* start;

    std::tuple<int, int, int> backgroundColorFor(Cell *cell) override;
    void setDistances(Distances* distances);
    Distances* distances;
private:
    void prepareGrid();
    Cell* farthest;
    int maximum;
};


#endif //MAZE_IN_CPP_POLARGRID_H
