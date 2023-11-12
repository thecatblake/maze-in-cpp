//
// Created by ryousuke kaga on 2023/11/11.
//

#include "MaskGrid.h"
#include <fstream>

MaskGrid::MaskGrid(std::unique_ptr<Mask>& mask):
    Grid(mask->rows, mask->columns),
    mask(std::move(mask)) {
    prepareGrid();
}

void MaskGrid::prepareGrid() {
    cells.resize(columns * rows);
    for(int i=0; i < cells.size(); i++) {
        int column = i % rows;
        int row = i / rows;
        if(!*(*mask)(row, column))
            cells[i] = nullptr;
        else {
            Cell* cell = new Cell(row, column);
            cells[i] = cell;
        }
    }

    for(auto & cell : cells) {
        if(!cell) continue;
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

std::unique_ptr<MaskGrid> MaskGrid::loadFile(const std::string& path) {
    std::ifstream f(path);
    std::string line;

    int i = 0;
    int width = 0;
    int height = 0;
    std::vector<int> masks;
    while(std::getline(f, line)) {
        width = std::max(width, (int)line.length());
        for (auto & c : line) {
            if(c == 'X')
                masks.push_back(i);
            i++;
        }
        height++;
    }

    auto mask = std::make_unique<Mask>(height, width);

    for(auto p : masks) {
        mask->bits[p] = false;
    }

    return std::make_unique<MaskGrid>(mask);
}

std::unique_ptr<MaskGrid> MaskGrid::loadPng(const std::string &path) {
    FILE *fp = fopen(path.c_str(), "rb");

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if(!png) abort();

    png_infop info = png_create_info_struct(png);
    if(!info) abort();

    if(setjmp(png_jmpbuf(png))) abort();

    png_init_io(png, fp);

    png_read_info(png, info);

    int width      = png_get_image_width(png, info);
    int height     = png_get_image_height(png, info);
    auto color_type = png_get_color_type(png, info);
    auto bit_depth  = png_get_bit_depth(png, info);
    png_bytep* row_pointers = nullptr;

    // Read any color_type into 8bit depth, RGBA format.
    // See http://www.libpng.org/pub/png/libpng-manual.txt

    if(bit_depth == 16)
        png_set_strip_16(png);

    if(color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);

    // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png);

    if(png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);

    // These color_type don't have an alpha channel then fill it with 0xff.
    if(color_type == PNG_COLOR_TYPE_RGB ||
       color_type == PNG_COLOR_TYPE_GRAY ||
       color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

    if(color_type == PNG_COLOR_TYPE_GRAY ||
       color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png);

    png_read_update_info(png, info);

    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for(int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
    }

    png_read_image(png, row_pointers);

    fclose(fp);

    png_destroy_read_struct(&png, &info, nullptr);

    int i=0;
    std::vector<int> masks;
    for(int y = 0; y < height; y++) {
        png_bytep row = row_pointers[y];
        for(int x = 0; x < width; x++) {
            png_bytep px = &(row[x * 4]);

            if(px[0] == 0 && px[1] == 0 && px[2] == 0)
                masks.push_back(i);

            i++;
        }
    }

    auto mask = std::make_unique<Mask>(height, width);

    for(auto p : masks) {
        mask->bits[p] = false;
    }

    return std::make_unique<MaskGrid>(mask);
}
