//
// Created by ryousuke kaga on 2023/11/22.
//

#include "HexCell.h"

std::vector<Cell *> HexCell::neighbors() {
    std::vector<Cell*> cells;
    if(northwest) cells.push_back(northwest);
    if(north) cells.push_back(north);
    if(northeast) cells.push_back(northeast);
    if(southwest) cells.push_back(southwest);
    if(south) cells.push_back(south);
    if(southeast) cells.push_back(southeast);
    return cells;
}

HexCell::HexCell(int row, int column):
    Cell(row, column),
    row(row),
    column(column),
    southeast(nullptr),
    southwest(nullptr),
    south(nullptr),
    northeast(nullptr),
    northwest(nullptr),
    north(nullptr)
    {

}
