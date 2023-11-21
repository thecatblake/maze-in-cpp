//
// Created by ryousuke kaga on 2023/11/22.
//

#ifndef MAZE_IN_CPP_HEXCELL_H
#define MAZE_IN_CPP_HEXCELL_H

#include "Cell.h"

class HexCell : public Cell {
public:
    HexCell(int row, int column);
    HexCell* northeast;
    HexCell* northwest;
    HexCell* southeast;
    HexCell* southwest;
    HexCell* south;
    HexCell* north;
    int row;
    int column;
    std::vector<Cell*> neighbors() override;
};


#endif //MAZE_IN_CPP_HEXCELL_H
