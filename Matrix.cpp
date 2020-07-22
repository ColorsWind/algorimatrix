//
// Created by colors_wind on 2020/7/22.
//

#include "Matrix.h"
Matrix::Matrix(int number): sizeM(1), sizeN(1), array(new int[0]) {
    this -> array[0] = number;
}

Matrix::Matrix(int sizeM, int sizeN): sizeM(sizeM), sizeN(sizeN), array(new int[sizeM * sizeN]) {}

Matrix::Matrix(int sizeM, int sizeN): sizeM(sizeM), sizeN(sizeN), array(new int[sizeM * sizeN]) {}

