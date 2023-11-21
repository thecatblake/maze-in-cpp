//
// Created by ryousuke kaga on 2023/11/22.
//

#include "HexGrid.h"
#include "HexCell.h"
#include <iostream>
#include <cmath>
#include <SDL.h>

HexGrid::HexGrid(int rows, int columns) : Grid(rows, columns), rows(rows), columns(columns) {
    prepareGrid();
}

void HexGrid::prepareGrid() {
    cells.resize(rows*columns);
    for(int row=0; row < rows; row++) {
        for(int column=0; column < columns; column++) {
            cells[row*columns + column] = new HexCell(row, column);
        }
    }

    for (auto & cell: cells) {
        int north_diagonal, south_diagonal;
        if(cell->column % 2 == 0) {
            north_diagonal = cell->row - 1;
            south_diagonal = cell->row;
        } else {
            north_diagonal = cell->row;
            south_diagonal = cell->row + 1;
        }

        cell->northwest = getCell(north_diagonal, cell->column - 1);
        cell->north = getCell(cell->row-1, cell->column);
        cell->northeast = getCell(north_diagonal, cell->column + 1);
        cell->southwest = getCell(south_diagonal, cell->column - 1);
        cell->south = getCell(cell->row + 1, cell->column);
        cell->southeast = getCell(south_diagonal, cell->column + 1);
    }
}

void HexGrid::toPng(char *file_name, int cell_size) {

}

HexCell *HexGrid::getCell(int row, int column) {
    if(column < 0 || column >= columns || row < 0 || row >= rows)
        return nullptr;
    return cells[row*columns + column];
}

HexCell *HexGrid::randomCell() {
    int column = _dist(_generator) % columns;
    int row = _dist(_generator) % rows;
    return getCell(row, column);
}

void HexGrid::show(int cell_size) {
    double a_size = cell_size / 2.0;
    double b_size = cell_size * sqrt(3) / 2.0;
    int width = cell_size * 2;
    int height = (int)b_size * 2;
    bool running = true;

    int img_width = (int)lround(3 * a_size * columns + a_size + 0.5);
    int img_height = (int)(lround(height * rows + b_size + 0.5));

    SDL_Window* window = SDL_CreateWindow(
            "hex_maze",
            100,
            100,
            img_width,
            img_height,
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

    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_Rect fill;
    fill.x = 0;
    fill.y = 0;
    fill.w = img_width;
    fill.h = img_height;
    SDL_RenderFillRect(render, &fill);

    for(auto & cell : cells) {
        int cx = (int)(cell_size + 3 * cell->column * a_size);
        int cy = (int)(b_size + cell->row * height);
        if(cell->column % 2 == 1) cy += (int)b_size;

        int x_fw = cx-cell_size;
        int x_nw = (int)(cx-a_size);
        int x_ne = (int)(cx + a_size);
        int x_fe = cx + cell_size;

        int y_n = (int)(cy - b_size);
        int y_m = cy;
        int y_s = (int)(cy + b_size);


        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        if(!cell->southwest)
            SDL_RenderDrawLine(render, x_fw, y_m, x_nw, y_s);
        if(!cell->northwest)
            SDL_RenderDrawLine(render, x_fw, y_m, x_nw, y_n);
        if(!cell->north)
            SDL_RenderDrawLine(render, x_nw, y_n, x_ne, y_n);
        if(!cell->linked(cell->northeast))
            SDL_RenderDrawLine(render, x_ne, y_n, x_fe, y_m);
        if(!cell->linked(cell->southeast))
            SDL_RenderDrawLine(render, x_fe, y_m, x_ne, y_s);
        if(!cell->linked(cell->south))
            SDL_RenderDrawLine(render, x_ne, y_s, x_nw, y_s);
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
