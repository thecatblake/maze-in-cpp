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
            std::string body = " " + content_of(cell) + " ";
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

void png_write_line(png_bytep* row_pointers, int x1, int y1, int x2, int y2) {
    for(int y=y1; y <= y2; y++) {
        png_bytep row = row_pointers[y];
        for(int x=x1; x <= x2; x++) {
            png_bytep px = &(row[x * 4]);
            px[0] = 0;
            px[1] = 0;
            px[2] = 0;
            px[3] = 255;
        }
    }
}

void Grid::toPng(char* file_name, int cell_size) {
    int img_width = cell_size * columns;
    int img_height = cell_size * rows;

    FILE* fp = fopen(file_name, "wb");
    if(!fp) return;

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) return;

    png_infop info = png_create_info_struct(png);
    if (!info) return;

    if (setjmp(png_jmpbuf(png))) return;

    png_init_io(png, fp);

    // Output is 8bit depth, RGBA format.
    png_set_IHDR(
            png,
            info,
            img_width + 1, img_height + 1,
            8,
            PNG_COLOR_TYPE_RGBA,
            PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_DEFAULT,
            PNG_FILTER_TYPE_DEFAULT
    );
    png_write_info(png, info);

    auto *row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * (img_height+1));
    for(int y = 0; y < (img_height+1); y++) {
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
    }

    for(int y = 0; y < img_height; y++) {
        png_bytep row = row_pointers[y];
        for(int x = 0; x < img_width; x++) {
            png_bytep px = &(row[x * 4]);
            px[0] = 255;
            px[1] = 255;
            px[2] = 255;
            px[3] = 255;
        }
    }

    for(auto & cell : cells) {
        int x1 = cell->column * cell_size;
        int y1 = cell->row * cell_size;
        int x2 = (cell->column + 1) * cell_size;
        int y2 = (cell->row + 1) * cell_size;

        if(!cell->north)
            png_write_line(row_pointers, x1, y1, x2, y1);
        if(!cell->west)
            png_write_line(row_pointers, x1, y1, x1, y2);
        if(!cell->linked(cell->east))
            png_write_line(row_pointers, x2, y1, x2, y2);
        if(!cell->linked(cell->south))
            png_write_line(row_pointers, x1, y2, x2, y2);
    }

    png_write_image(png, row_pointers);
    png_write_end(png, info);

    for(int y = 0; y < img_height; y++) {
        free(row_pointers[y]);
    }
    free(row_pointers);

    fclose(fp);

    png_destroy_write_struct(&png, &info);
}

std::string Grid::content_of(Cell *cell) {
    return " ";
}
