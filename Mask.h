//
// Created by ryousuke kaga on 2023/11/11.
//

#ifndef MAZE_IN_CPP_MASK_H
#define MAZE_IN_CPP_MASK_H

#include <vector>
#include <random>

class Mask {
public:
    Mask(int rows, int columns);
    std::vector<bool>::iterator operator()(int row, int column);
    std::pair<int, int> randomLocation();
    int count();
    int rows;
    int columns;
    std::vector<bool> bits;
private:
    std::default_random_engine _generator;
    std::uniform_int_distribution<int> _dist;
};


#endif //MAZE_IN_CPP_MASK_H
