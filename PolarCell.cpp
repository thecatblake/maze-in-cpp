//
// Created by ryousuke kaga on 2023/11/15.
//

#include "PolarCell.h"

std::vector<Cell *> PolarCell::neighbors() {
    std::vector<Cell*> list;
    if(cw) list.push_back(cw);
    if(ccw) list.push_back(ccw);
    if(inward) list.push_back(inward);

    for(auto & cell : outward) {
        if(cell) list.push_back(cell);
    }

    return list;
}

PolarCell::PolarCell(int row, int column) :
    Cell(row, column),
    row(row),
    column(column),
    cw(nullptr),
    ccw(nullptr),
    inward(nullptr){

}
