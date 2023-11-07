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

Distances *Distances::pathTo(Cell *cell) {
    Cell* current = cell;

    auto breadcrumbs = new Distances(root);
    breadcrumbs->cells[cell] = cells[current];

    while(current != root) {
        for(auto & neighbor : current->links) {
            if(cells[neighbor] < cells[current]) {
                breadcrumbs->cells[neighbor] = cells[neighbor];
                current = neighbor;
                break;
            }
        }
    }

    return breadcrumbs;
}
