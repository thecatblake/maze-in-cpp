//
// Created by ryousuke kaga on 2023/11/22.
//

#ifndef MAZE_IN_CPP_HEXGRID_H
#define MAZE_IN_CPP_HEXGRID_H

#include "Grid.h"
#include "HexCell.h"

class HexGrid : public Grid {
public:
    HexGrid(int rows, int columns);
    std::vector<HexCell*> cells;
    HexCell* getCell(int row, int column) override;
    HexCell* randomCell() override;
    void toPng(char* file_name, int cell_size);
    void show(int cell_size);
    int rows;
    int columns;
    HexCell* start;
    Distances* distances;
private:
    void prepareGrid();
    Cell* farthest;
    int maximum;
};


#endif //MAZE_IN_CPP_HEXGRID_H
