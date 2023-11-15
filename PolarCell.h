//
// Created by ryousuke kaga on 2023/11/15.
//

#ifndef MAZE_IN_CPP_POLARCELL_H
#define MAZE_IN_CPP_POLARCELL_H

#include "Cell.h"

class PolarCell : public Cell {
public:
    PolarCell(int row, int column);
    std::vector<Cell*> neighbors() override;
    PolarCell* cw;
    PolarCell* ccw;
    PolarCell* inward;
    std::vector<PolarCell*> outward;
    int row;
    int column;
};


#endif //MAZE_IN_CPP_POLARCELL_H
