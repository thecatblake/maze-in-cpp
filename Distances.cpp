//
// Created by ryousuke kaga on 2023/11/08.
//

#include "Distances.h"

Distances::Distances(Cell *cell): root(cell) {

}

int &Distances::operator[](Cell *cell) {
    return cells[cell];
}

bool Distances::calculated(Cell *cell) {
    return cells.find(cell) != cells.end();
}
