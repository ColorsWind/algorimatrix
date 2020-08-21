//
// Created by colors_wind on 2020/7/22.
//

#ifndef ALGORIMATRIX_MATRIX_H
#define ALGORIMATRIX_MATRIX_H

class Matrix {
private:
    int m_row;
    int m_col;
    double* m_array;
public:
    Matrix(int row, int col);
    Matrix(int row, int col, double* array);
    Matrix & operator+=(Matrix m);
    Matrix & operator-=(Matrix m);
    Matrix & operator*=(Matrix m);
    Matrix & operator/=(Matrix m);
    Matrix friend operator+(Matrix m1, Matrix m2);
    Matrix friend operator-(Matrix m1, Matrix m2);
    Matrix friend operator*(Matrix m1, Matrix m2);
    Matrix friend operator/(Matrix m1, Matrix m2);
    double & at(int row, int col);
    int size();
};

#endif ALGORIMATRIX_MATRIX_H
