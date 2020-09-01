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
    Matrix & operator+=(const Matrix & m);
    Matrix & operator-=(const Matrix & m);
    Matrix & operator*=(const Matrix & m);
    Matrix & operator/=(const Matrix & m);
    Matrix friend operator+(const Matrix m1, const Matrix m2);
    Matrix friend operator-(const Matrix m1, const Matrix m2);
    Matrix friend operator*(const Matrix m1, const Matrix m2);
    Matrix friend operator/(const Matrix m1, const Matrix m2);
    double det() const;
    Matrix inverse() const;
    inline double & at(int row, int col);
    inline double read(int row, int col) const;
    int size() const;
    void swapRow(int i, int j);
    void swapCol(int i, int j);
    Matrix adjoint() const;
    Matrix cofactor(int i, int j) const;
    Matrix function(double (func)(double)) const;
};

#endif ALGORIMATRIX_MATRIX_H
