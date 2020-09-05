//
// Created by colors_wind on 2020/7/22.
//

#ifndef ALGORIMATRIX_MATRIX_H
#define ALGORIMATRIX_MATRIX_H

#include "ObjectMatrix.h"
#include <iostream>
#include <vector>

using std::string;
using std::vector;

class Matrix : public ObjectMatrix<double> {
public:
    Matrix();
    Matrix(const Matrix &matrix);
    explicit Matrix(double number);
    Matrix(int row, int col);
    Matrix(int row, int col, double* array);
    Matrix & operator=(const Matrix & m);
    Matrix & operator+=(const Matrix & m);
    Matrix & operator-=(const Matrix & m);
    Matrix & operator*=(const Matrix & m);
    Matrix & operator/=(const Matrix & m);

    Matrix friend operator+(const Matrix& m1, const Matrix& m2);
    Matrix friend operator+(const Matrix& m);
    Matrix friend operator-(const Matrix& m1, const Matrix& m2);
    Matrix friend operator-(const Matrix& m);
    Matrix friend operator*(const Matrix& m1, const Matrix& m2);
    Matrix friend operator*(const Matrix& matrix, double factor);
    Matrix friend operator*(double factor, const Matrix& matrix);
    Matrix friend operator/(const Matrix& m1, const Matrix& m2);
    Matrix friend fromBlock(ObjectMatrix<Matrix> block);

    // primary line transformation
    void addByAnother(int i, int j, double factor=1.0);
    void multiplyLine(int i, double factor);
    void swapLine(int i, int j);
    void upperTriangular();

    // calculation of matrix attributes
    double det() const;
    int rank() const;
    Matrix inverse() const;
    Matrix sub(int row1, int row2, int col1, int col2) const;
    Matrix adjoint() const;
    Matrix cofactor(int i, int j) const;
    Matrix transpose() const;

    string toString() const;

    Matrix traverse(double (func)(double)) const;
    Matrix traverse(double (func)(double,double), const Matrix &parameter) const;
};

Matrix zeros(int row);
Matrix zeros(int row, int col);

Matrix identity(int n, double factor=1.0);

typedef Matrix (*Func)(const vector<Matrix>&);

#endif ALGORIMATRIX_MATRIX_H
