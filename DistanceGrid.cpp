//
// Created by ryousuke kaga on 2023/11/08.
//

#include "DistanceGrid.h"
#include <cstdlib>

std::string DistanceGrid::content_of(Cell *cell) {
    if(distances && distances->calculated(cell)) {
        return b36[distances->cells[cell] % b36.size()];
    } else {
        return Grid::content_of(cell);
    }
}

DistanceGrid::DistanceGrid(int rows, int columns): Grid(rows, columns) {
    b36[0] = "0";
    b36[1] = "1";
    b36[2] = "2";
    b36[3] = "3";
    b36[4] = "4";
    b36[5] = "5";
    b36[6] = "6";
    b36[7] = "7";
    b36[8] = "8";
    b36[9] = "9";
    b36[10] = "A";
    b36[11] = "B";
    b36[12] = "C";
    b36[13] = "D";
    b36[14] = "E";
    b36[15] = "F";
    b36[16] = "G";
    b36[17] = "H";
    b36[18] = "I";
    b36[19] = "J";
    b36[20] = "K";
    b36[21] = "L";
    b36[22] = "M";
    b36[23] = "O";
    b36[24] = "P";
    b36[25] = "Q";
    b36[26] = "R";
    b36[27] = "S";
    b36[28] = "T";
    b36[29] = "U";
    b36[30] = "V";
    b36[31] = "W";
    b36[32] = "X";
    b36[33] = "Y";
    b36[34] = "Z";
    b36[35] = "å";
    b36[36] = "∫";
    b36[37] = "ç";
    b36[38] = "∂";
    b36[39] = "´";
    b36[40] = "ƒ";
    b36[41] = "©";
}
