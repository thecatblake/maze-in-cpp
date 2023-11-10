//
// Created by ryousuke kaga on 2023/11/08.
//

#include "ColoredGrid.h"
#include <iostream>

void ColoredGrid::setDistances(Distances *ds) {
    distances = ds;
    auto [m_c, m_d] = distances->max();
    farthest = m_c;
    maximum = m_d;
}

std::tuple<int, int, int> ColoredGrid::backgroundColorFor(Cell *cell) {
    if(distances->cells.find(cell) == distances->cells.end())
        return std::make_tuple(255, 255, 255);
    int distance = distances->cells[cell];
    double intensity = (double)(maximum - distance) / maximum;
    int dark = (int)floor((255 * intensity));
    int bright = 128 + (int)floor((127*intensity));
    return std::make_tuple(dark, bright, dark);
}
