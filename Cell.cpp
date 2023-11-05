//
// Created by ryousuke kaga on 2023/11/05.
//

#include "Cell.h"

Cell::Cell(int row, int column):
    row(row),
    column(column),
    north(nullptr),
    south(nullptr),
    east(nullptr),
    west(nullptr) {

}

Cell* Cell::link(Cell* cell, bool bidi) {
    links.insert(cell);
    if(bidi)
        cell->link(this, false);

    return this;
}

Cell* Cell::unlink(Cell* cell, bool bidi) {
    links.erase(cell);
    if(bidi)
        cell->unlink(this, false);

    return this;
}

bool Cell::linked(Cell* cell) {
    return links.find(cell) != links.end();
}

std::vector<Cell *> Cell::neighbors() {
    std::vector<Cell*> xs;
    if(north) xs.push_back(north);
    if(south) xs.push_back(south);
    if(east) xs.push_back(east);
    if(west) xs.push_back(west);

    return xs;
}
