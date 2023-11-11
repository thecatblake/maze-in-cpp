//
// Created by ryousuke kaga on 2023/11/11.
//

#include "MaskGrid.h"

MaskGrid::MaskGrid(Mask *mask):
    Grid(mask->rows, mask->columns),
    mask(mask) {
    prepareGrid();
}

void MaskGrid::prepareGrid() {
    cells.resize(columns * rows);
    for(int i=0; i < cells.size(); i++) {
        int column = i % rows;
        int row = i / rows;
        if(*(*mask)(row, column))
            cells[i] = nullptr;

        Cell* cell = new Cell(row, column);
        cells[i] = cell;
    }

    for(auto & cell : cells) {
        cell->north = getCell(cell->row - 1, cell->column);
        cell->south = getCell(cell->row + 1, cell->column);
        cell->west = getCell(cell->row, cell->column - 1);
        cell->east = getCell(cell->row, cell->column + 1);
    }
}

Cell *MaskGrid::randomCell() {
    auto [row, column] = mask->randomLocation();
    return getCell(row, column);
}

Cell *MaskGrid::getCell(int row, int column) {
    if(column < 0 || column >= columns || row < 0 || row >= rows || !*(*mask)(row, column))
        return nullptr;

    return cells[row * rows + column];
}
