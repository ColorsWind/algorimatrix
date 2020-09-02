//
// Created by colors_wind on 2020/7/22.
//

#ifndef ALGORIMATRIX_MATRIX_H
#define ALGORIMATRIX_MATRIX_H

#include <iostream>
#include <vector>

using std::string;
using std::vector;

class Matrix {
private:
    int m_row;
    int m_col;
    double* m_array;
public:
    ~Matrix();
    Matrix(const Matrix &matrix);
    Matrix(double number);
    Matrix(int row, int col);
    Matrix(int row, int col, double* array);
    Matrix(vector<double> &array);
    Matrix & operator=(const Matrix & m);
    Matrix & operator+=(const Matrix & m);
    Matrix & operator-=(const Matrix & m);
    Matrix & operator*=(const Matrix & m);
    Matrix & operator/=(const Matrix & m);
    double & operator[](const int k);
    Matrix friend operator+(const Matrix m1, const Matrix m2);
    Matrix friend operator+(const Matrix m);
    Matrix friend operator-(const Matrix m1, const Matrix m2);
    Matrix friend operator-(const Matrix m);
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
    string toString() const;
    int getRow() const;
    int getCol() const;
    Matrix traverse(double (func)(double)) const;
    Matrix traverse(double (func)(double,double), Matrix &parameter) const;
};

typedef Matrix (*Func1)(Matrix&);
typedef Matrix (*Func2)(Matrix&, Matrix&);

#endif ALGORIMATRIX_MATRIX_H
