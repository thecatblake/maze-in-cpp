//
// Created by ryousuke kaga on 2023/11/05.
//

#include "Grid.h"
#include <SDL.h>

Grid::Grid(int rows, int columns):
    rows(rows),
    columns(columns),
    _dist(std::max(rows, columns)),
    start(nullptr){
    prepareGrid();
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
            std::string east_boundary = cell && cell->linked(cell->east) ? " " : "|";
            top += body + east_boundary;

            std::string south_boundary = cell && cell->linked(cell->south) ? "   " : "---";
            bottom += south_boundary + "+";
        }
        output += top + "\n";
        output += bottom + "\n";
    }

    return output;
}

void png_write_line(png_bytep* row_pointers, int x1, int y1, int x2, int y2, std::tuple<int, int, int> color) {
    if(y1 == y2) {
        png_bytep row = row_pointers[y1];

        if (x1 >= x2) {
            std::swap(y1, y2);
            std::swap(x1, x2);
        }
        for(int x=x1; x <= x2; x++) {
            png_bytep px = &(row[x * 4]);
            px[0] = std::get<0>(color);
            px[1] = std::get<1>(color);
            px[2] = std::get<2>(color);
            px[3] = 255;
        }

        return;
    }

    if (y1 >= y2) {
        std::swap(y1, y2);
        std::swap(x1, x2);
    }

    if(x1 == x2)  {
        for(int y=y1; y <= y2; y++) {
            png_bytep row = row_pointers[y];

            png_bytep px = &(row[x1 * 4]);
            px[0] = std::get<0>(color);
            px[1] = std::get<1>(color);
            px[2] = std::get<2>(color);
            px[3] = 255;
        }

        return;
    }

    double s = (y1 - y2) / (double)(x1 - x2);
    for(int y=y1; y <= y2; y++) {
        png_bytep row = row_pointers[y];
        int x = (int)((y - y1) / s + x1);
        png_bytep px = &(row[x * 4]);
        px[0] = std::get<0>(color);
        px[1] = std::get<1>(color);
        px[2] = std::get<2>(color);
        px[3] = 255;
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
            px[0] = 0;
            px[1] = 0;
            px[2] = 0;
            px[3] = 255;
        }
    }

    for(auto & cell : cells) {
        if(!cell) continue;
        int x1 = cell->column * cell_size;
        int y1 = cell->row * cell_size;
        int x2 = (cell->column + 1) * cell_size;
        int y2 = (cell->row + 1) * cell_size;

        auto color = backgroundColorFor(cell);
        png_write_line(row_pointers, x1, y1, x2, y2, color);
    }

    for(auto & cell : cells) {
        if(!cell) continue;
        int x1 = cell->column * cell_size;
        int y1 = cell->row * cell_size;
        int x2 = (cell->column + 1) * cell_size;
        int y2 = (cell->row + 1) * cell_size;

        if(!cell->north)
            png_write_line(row_pointers, x1, y1, x2, y1, std::make_tuple(0, 0, 0));
        if(!cell->west)
            png_write_line(row_pointers, x1, y1, x1, y2, std::make_tuple(0, 0, 0));
        if(!cell->linked(cell->east))
            png_write_line(row_pointers, x2, y1, x2, y2, std::make_tuple(0, 0, 0));
        if(!cell->linked(cell->south))
            png_write_line(row_pointers, x1, y2, x2, y2, std::make_tuple(0, 0, 0));
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

std::tuple<int, int, int> Grid::backgroundColorFor(Cell *cell) {
    return std::make_tuple(255, 255, 255);
}

std::vector<Cell*> Grid::deadends() {
    std::vector<Cell*> ds;

    for(auto & cell : cells) {
        if(cell->links.size() == 1)
            ds.push_back(cell);
    }

    return ds;
}

void Grid::prepareGrid() {
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

void Grid::show(int cell_size) {
    int width = cell_size * columns;
    int height = cell_size * rows;
    bool running = true;

     SDL_Window* window = SDL_CreateWindow(
            "maze",
            100,
            100,
            width,
            height,
            0
    );

    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return;
    }

    SDL_Renderer* render = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED
    );

    SDL_RenderClear(render);

    for(auto & cell : cells) {
        if(!cell) continue;
        int x1 = cell->column * cell_size;
        int y1 = cell->row * cell_size;
        int x2 = (cell->column + 1) * cell_size;
        int y2 = (cell->row + 1) * cell_size;

        auto color = backgroundColorFor(cell);
        SDL_SetRenderDrawColor(render, std::get<0>(color), std::get<1>(color), std::get<2>(color), 255);
        SDL_Rect rect;
        rect.x = x1;
        rect.y = y1;
        rect.w = x2;
        rect.h = y2;
        SDL_RenderFillRect(render, &rect);
    }

    for(auto & cell : cells) {
        if(!cell) continue;
        int x1 = cell->column * cell_size;
        int y1 = cell->row * cell_size;
        int x2 = (cell->column + 1) * cell_size;
        int y2 = (cell->row + 1) * cell_size;

        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        if(!cell->north)
            SDL_RenderDrawLine(render, x1, y1, x2, y1);
        if(!cell->west)
            SDL_RenderDrawLine(render, x1, y1, x1, y2);
        if(!cell->linked(cell->east))
            SDL_RenderDrawLine(render, x2, y1, x2, y2);
        if(!cell->linked(cell->south))
            SDL_RenderDrawLine(render, x1, y2, x2, y2);
    }

    SDL_RenderPresent(render);

    SDL_Event event;

    while(running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }

    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    SDL_Quit();
}
