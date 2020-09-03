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
    Matrix();
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
    double & operator[](const int k) const;
    Matrix friend operator+(const Matrix m1, const Matrix m2);
    Matrix friend operator+(const Matrix m);
    Matrix friend operator-(const Matrix m1, const Matrix m2);
    Matrix friend operator-(const Matrix m);
    Matrix friend operator*(const Matrix m1, const Matrix m2);
    Matrix friend operator*(const Matrix matrix, const double factor);
    Matrix friend operator*(const double factor, const Matrix matrix);
    Matrix friend operator/(const Matrix m1, const Matrix m2);

    // primary line transformation
    void addByAnother(int i, int j, double factor=1.0);
    void multiplyLine(int i, double factor);
    void swapLine(int i, int j);

    void upperTriangular();
    double det() const;
    int rank() const;
    Matrix inverse() const;

    Matrix sub(int row1, int row2, int col1, int col2) const;
    inline int firstIndex(int row) const;
    inline double & at(int row, int col);
    inline double read(int row, int col) const;
    int size() const;
    Matrix adjoint() const;
    Matrix cofactor(int i, int j) const;
    string toString() const;
    int getRow() const;
    int getCol() const;
    Matrix traverse(double (func)(double)) const;
    Matrix traverse(double (func)(double,double), const Matrix &parameter) const;
};

Matrix zeros(int row);
Matrix zeros(int row, int col);

Matrix identity(int n, double factor=1.0);

typedef Matrix (*Func)(const vector<Matrix>&);

#endif ALGORIMATRIX_MATRIX_H
