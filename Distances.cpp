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

std::pair<Cell *, int> Distances::max() {
    int m_d = 0;
    auto m_c = root;

    for(auto& [cell, distance] : cells) {
        if(distance > m_d) {
            m_c = cell;
            m_d = distance;
        }
    }
    return std::make_pair(m_c, m_d);
}
