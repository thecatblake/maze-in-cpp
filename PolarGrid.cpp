//
// Created by ryousuke kaga on 2023/11/15.
//

#include "PolarGrid.h"
#include "PolarCell.h"
#include <iostream>
#include <cmath>

void PolarGrid::toPng(char *file_name, int cell_size) {
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

    int img_size = 2 * rows * cell_size;

    // Output is 8bit depth, RGBA format.
    png_set_IHDR(
            png,
            info,
            img_size + 1, img_size + 1,
            8,
            PNG_COLOR_TYPE_RGBA,
            PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_DEFAULT,
            PNG_FILTER_TYPE_DEFAULT
    );
    png_write_info(png, info);

    auto *row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * (img_size+1));
    for(int y = 0; y < (img_size+1); y++) {
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
    }

    for(int y = 0; y < img_size; y++) {
        png_bytep row = row_pointers[y];
        for(int x = 0; x < img_size; x++) {
            png_bytep px = &(row[x * 4]);
            px[0] = 255;
            px[1] = 255;
            px[2] = 255;
            px[3] = 255;
        }
    }

    int center = img_size / 2;
    for(auto & row : cells) {
        for(auto & cell : row) {
            if(cell->row == 0) continue;
            double theta = 2 * M_PI / (int)cells[cell->row].size();
            double inner_radius = cell->row * cell_size;
            double outer_radius = (cell->row + 1) * cell_size;
            double theta_ccw = cell->column * theta;
            double theta_cw = (cell->column + 1) * theta;

            int ax = center + (int)(inner_radius * std::cos(theta_ccw));
            int ay = img_size - center + (int)(inner_radius * std::sin(theta_ccw));
            int bx = center + (int)(outer_radius * std::cos(theta_ccw));
            int by = img_size - center + (int)(outer_radius * std::sin(theta_ccw));
            int cx = center + (int)(inner_radius * std::cos(theta_cw));
            int cy =  center + (int)(inner_radius * std::sin(theta_cw));
            int dx = center + (int)(outer_radius * std::cos(theta_cw));
            int dy = center + (int)(outer_radius * std::sin(theta_cw));

            if(!cell->linked(cell->inward))
                png_write_line(row_pointers, ax, ay, cx, cy, std::make_tuple(0, 0, 0));
            if(!cell->linked(cell->cw))
                png_write_line(row_pointers, cx, cy, dx, dy, std::make_tuple(0, 0, 0));
        }
    }

    int xp = center + center;
    int yp = center;

    for(int t=1; t <= 5000; t++) {
        double theta = (2 * M_PI / 5000) * t ;
        int xt = center + (int)(center * std::cos(theta));
        int yt = img_size - center + (int)(center * std::sin(theta));
        png_write_line(row_pointers, xp, yp, xt, yt, std::make_tuple(0, 0, 0));

        xp = xt;
        yp = yt;
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

PolarGrid::PolarGrid(int rows) : Grid(rows, 1), rows(rows) {
    prepareGrid();
}

void PolarGrid::prepareGrid() {
    cells.resize(rows);
    double row_height = 1.0 / rows;
    cells[0] = {new PolarCell(0, 0)};

    for(int row=1; row < rows; row++) {
        double radius = (double)row / rows;
        double circumference = 2 * M_PI * radius;

        auto previous_count = cells[row - 1].size();
        auto estimated_cell_width = circumference / (double)previous_count;
        auto ratio = std::ceil(estimated_cell_width / row_height);

        size_t n = previous_count * ratio;
        cells[row].resize(n);
        for(int col=0; col < n; col++) {
            cells[row][col] = new PolarCell(row, col);
        }
    }

    for(auto & row : cells) {
        for(auto & cell : row) {
            if(cell->row > 0) {
                cell->cw = getCell(cell->row, cell->column + 1);
                cell->ccw = getCell(cell->row, cell->column - 1);

                double ratio = (double)cells[cell->row].size() / (double)cells[cell->row - 1].size();
                auto parent = cells[cell->row - 1][cell->column / ratio];
                parent->outward.push_back(cell);
                cell->inward = parent;
            }
        }
    }
}

PolarCell *PolarGrid::getCell(int row, int column) {
    if(row < 0 || row >= rows)
        return nullptr;

    return cells[row][column % cells[row].size()];
}

PolarCell *PolarGrid::randomCell() {
    auto row = cells[_dist(_generator) % rows];
    std::uniform_int_distribution<int> dist(0, (int)row.size());

    return row[dist(_generator) % row.size()];
}

std::tuple<int, int, int> PolarGrid::backgroundColorFor(Cell *cell) {
    if(distances->cells.find(cell) == distances->cells.end())
        return std::make_tuple(255, 255, 255);
    int distance = distances->cells[cell];
    double intensity = (double)(maximum - distance) / maximum;
    int dark = (int)floor((255 * intensity));
    int bright = 128 + (int)floor((127*intensity));
    return std::make_tuple(dark, bright, dark);
}

void PolarGrid::setDistances(Distances *ds) {
    distances = ds;
    auto [m_c, m_d] = distances->max();
    farthest = m_c;
    maximum = m_d;
}
