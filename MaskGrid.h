//
// Created by ryousuke kaga on 2023/11/11.
//

#ifndef MAZE_IN_CPP_MASKGRID_H
#define MAZE_IN_CPP_MASKGRID_H

#include "Grid.h"
#include "Mask.h"

class MaskGrid : public Grid {
public:
    MaskGrid(std::unique_ptr<Mask>& mask);
    Cell* getCell(int row, int column);
    Cell* randomCell();
    static std::unique_ptr<MaskGrid> loadFile(const std::string& path);
    static std::unique_ptr<MaskGrid> loadPng(const std::string& path);
    std::unique_ptr<Mask> mask;
protected:
    void prepareGrid();
};


#endif //MAZE_IN_CPP_MASKGRID_H
