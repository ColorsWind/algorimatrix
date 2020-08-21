#include "Matrix.h"


Matrix::Matrix(int row, int col) : m_row(row), m_col(col), m_array(new double[row * col]) {}

Matrix::Matrix(int row, int col, double *array) : m_row(row), m_col(col), m_array(array) {}

Matrix &Matrix::operator+=(const Matrix & m) {
    for (int i = 0; i < size(); i++)
        this->m_array[i] += m.m_array[i];
    return *this;
};

Matrix &Matrix::operator-=(const Matrix & m) {
    for (int i = 0; i < size(); i++)
        this->m_array[i] -= m.m_array[i];
    return *this;
};

Matrix &Matrix::operator*=(const Matrix & m) {
    m_col = m.m_col;
    for (int i = 0; i < m_row; i++)
        for (int j = 0; j < m_col; j++) {
            int v = 0;
            for (int k = 0; k < m.m_row; k++)
                v += at(i, k) * m.read(k, j);
        }
    return *this;
}

Matrix &Matrix::operator/=(const Matrix & m) {
    *this *= m.inverse();
}

void Matrix::swapRow(int i, int j) {
    double temp;
    for (int k = 0; k < m_col; k++) {
        temp = at(i, k);
        at(i, k) = at(j, k);
        at(j, k) = temp;
    }
}

void Matrix::swapCol(int i, int j) {
    double temp;
    for (int k = 0; k < m_row; k++) {
        temp = at(k, i);
        at(k, i) = at(k, j);
        at(k, j) = temp;
    }
}

double Matrix::det() const {
    Matrix copy = *this;
    int ii, jj, k, u;
    int iter = 0;  //记录行变换的次数（交换）
    double result = 1, yin;
    int n = m_row;
    for (ii = 0; ii < n; ii++) {
        if (copy.at(ii, ii) == 0)

            for (jj = ii; jj < n; jj++) {
                if (copy.at(jj, ii) != 0) {
                    copy.swapRow(ii, jj);
                    iter++;
                }
            }

        for (k = ii + 1; k < n; k++) {
            yin = -1 * copy.at(k, ii) / copy.at(ii, ii);

            for (u = 0; u < n; u++) {
                copy.at(k, u) = copy.at(k, u) + copy.at(ii, u) * yin;
            }
        }
    }
    for (ii = 0; ii < n; ii++)  //求对角线的积 即 行列式的值
        result = result * copy.at(ii, ii);
    //行变换偶数次符号不变
    if (iter % 2 == 1)
        result = -result;
    return (result);
}

int Matrix::size() const{
    return m_row * m_col;
}

double &Matrix::at(int row, int col) {
    return m_array[row * m_col + col];
}

double Matrix::read(int row, int col) const{
    return m_array[row * m_col + col];
}

Matrix Matrix::cofactor(int row, int col) const{
    Matrix matrix(m_row - 1, m_col - 1);
    int k = 0;
    for (int i = 0; i < m_row; i++) {
        if (i == row) continue;
        for (int j = 0; j < m_col; j++) {
            if (j == col) continue;
            matrix.m_array[k] = read(row, col);
            k++;
        }
    }
    return matrix;
}

Matrix Matrix::inverse() const{
    Matrix matrix = adjoint();
    double det = this -> det();
    for (int k = 0; k < matrix.size(); k++) {
        matrix.m_array[k] /= det;
    }
    return matrix;
}

Matrix Matrix::function(double (func)(double)) const{
    Matrix matrix = *this;
    for (int k = 0; k < matrix.size(); k++) {
        matrix.m_array[k] = func(matrix.m_array[k]);
    }
    return  matrix;
}

Matrix Matrix::adjoint() const{
    Matrix matrix = *this;
    for (int i = 0; i < m_row; i++) {
        for (int j = 0; j < m_col; j++) {
            matrix.at(i, j) = cofactor(i, j).det();
        }
    }
}

Matrix operator+(const Matrix m1, const Matrix m2) {
    Matrix matrix = m1;
    matrix += m2;
    return m1;
}

Matrix operator-(const Matrix m1, const Matrix m2) {
    Matrix matrix = m1;
    matrix-= m2;
    return matrix;
}

Matrix operator*(const Matrix m1, const Matrix m2) {
    Matrix matrix = m1;
    matrix *= m2;
    return matrix;
}

Matrix operator/(const Matrix m1, const Matrix m2) {
    Matrix matrix = m1;
    matrix /= m2;
    return matrix;
}





