//
// Created by colors_wind on 2020/7/22.
//

#ifndef ALGORIMATRIX_MATRIX_H
#define ALGORIMATRIX_MATRIX_H
//
// Created by colors_wind on 2020/7/22.
//

#ifndef ALGORIMATRIX_MATRIX_H
#define ALGORIMATRIX_MATRIX_H

#endif //ALGORIMATRIX_MATRIX_H

class Matrix {
private:
    const int sizeM;
    const int sizeN;
    const int* array;
public:
    Matrix(int number);
    Matrix(int sizeM, int sizeN);
    Matrix(int sizeM, int sizeN, int* array);
    Materix friend operator+(Matrix m1, Matrix m2);
};

#endif //ALGORIMATRIX_MATRIX_H
