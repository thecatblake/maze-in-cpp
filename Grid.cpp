//
// Created by ryousuke kaga on 2023/11/05.
//

#include "Grid.h"

Grid::Grid(int rows, int columns):
    rows(rows),
    columns(columns),
    _dist(std::max(rows, columns)) {
    cells.resize(columns * rows);
    for(int i=0; i < cells.size(); i++) {
        int column = i % rows;
        int row = i / rows;
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

Grid::~Grid() {
    for(auto & cell : cells) {
        delete cell;
    }
}

Cell *Grid::getCell(int row, int column) {
    if(column < 0 || column >= columns || row < 0 || row >= rows)
        return nullptr;

    return cells[row * rows + column];
}

Cell *Grid::operator[](std::pair<int, int> index) {
    return getCell(index.first, index.second);
}

Cell *Grid::randomCell() {
    int column = _dist(_generator) % columns;
    int row = _dist(_generator) % rows;
    return getCell(row, column);
}

std::string Grid::toString() {
    std::string output = "+";
    for(int i=0; i < columns; i++)
        output += "---+";
    output += "\n";

    for(int row=0; row < rows; row++) {
        std::string top = "|";
        std::string bottom = "+";
        for(int column=0; column < columns; column++) {
            Cell* cell = getCell(row, column);
            std::string body = "   ";
            std::string east_boundary = cell->linked(cell->east) ? " " : "|";
            top += body + east_boundary;

            std::string south_boundary = cell->linked(cell->south) ? "   " : "---";
            bottom += south_boundary + "+";
        }
        output += top + "\n";
        output += bottom + "\n";
    }

    return output;
}
