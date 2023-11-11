//
// Created by ryousuke kaga on 2023/11/11.
//

#include "Mask.h"

Mask::Mask(int rows, int columns): rows(rows), columns(columns) {
    bits.resize(columns * rows);
    std::fill(bits.begin(), bits.end(), true);
}

std::vector<bool>::iterator Mask::operator()(int row, int column) {
    return bits.begin() + row * rows + column;
}

int Mask::count() {
    int c = 0;
    for(auto t : bits) {
        if(t) c++;
    }

    return c;
}

std::pair<int, int> Mask::randomLocation() {
    int column = _dist(_generator) % columns;
    int row = _dist(_generator) % rows;

    while(!*operator()(row, column)) {
        column = _dist(_generator) % columns;
        row = _dist(_generator) % rows;
    }

    return std::make_pair(row, column);
}
