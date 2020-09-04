#include "Matrix.h"
#include "MatrixFunc.h"
#include <sstream>
using std::to_string;
using std::copy;
using std::cerr;
using std::endl;

Matrix identity(int n, double factor) {
    Matrix matrix = zeros(n);
    for(int k=0;k<n;k++) {
        matrix.at(k, k) = factor;
    }
    return matrix;
}

Matrix::Matrix(int row, int col) : ObjectMatrix<double>(row, col) {}

Matrix::Matrix(const Matrix &matrix) = default;

Matrix::Matrix(int row, int col, double *array) : ObjectMatrix<double>(row, col, array) {}

Matrix &Matrix::operator=(const Matrix & m) {
    ObjectMatrix::operator=(m);
    return *this;
}

Matrix &Matrix::operator+=(const Matrix & m) {
    for (int i = 0; i < size(); i++)
        this->m_array[i] += m.m_array[i];
    return *this;
}

Matrix &Matrix::operator-=(const Matrix & m) {
    for (int i = 0; i < size(); i++)
        this->m_array[i] -= m.m_array[i];
    return *this;
}

Matrix &Matrix::operator*=(const Matrix & m) {
    *this = *this * m;
    return *this;
}

Matrix &Matrix::operator/=(const Matrix & m) {
    *this *= m.inverse();
    return *this;
}

Matrix Matrix::cofactor(int row, int col) const{
    Matrix matrix(m_row - 1, m_col - 1);
    int k = 0;
    for (int i = 0; i < m_row; i++) {
        if (i == row) continue;
        for (int j = 0; j < m_col; j++) {
            if (j == col) continue;
            matrix[k] = at(i, j);
            k++;
        }
    }
    return matrix;
}



Matrix Matrix::traverse(double (func)(double)) const{
    Matrix matrix(m_row, m_col);
    for (int k = 0; k < matrix.size(); k++) {
        matrix[k] = func(m_array[k]);
    }
    return  matrix;
}


Matrix Matrix::traverse(double (*func)(double, double), const Matrix &parameter) const {
    Matrix matrix(m_row, m_col);
    for(int k=0;k<matrix.size();k++) {
        matrix[k] = func(m_array[k], parameter.m_array[k]);
    }
    return matrix;
}



Matrix operator+(const Matrix& m1, const Matrix& m2) {
    Matrix matrix = m1;
    matrix += m2;
    return m1;
}

Matrix operator-(const Matrix& m1, const Matrix& m2) {
    Matrix matrix = m1;
    matrix-= m2;
    return matrix;
}
Matrix operator*(double factor, const Matrix& matrix) {
    Matrix multiply(matrix);
    for(int k=0;k<multiply.size();k++) multiply[k] *= factor;
    return multiply;
}

Matrix operator*(const Matrix& matrix, double factor) {
    return operator*(factor, matrix);
}

Matrix operator*(const Matrix& m1, const Matrix& m2) {
    if (m1.size() == 1) {
        return operator*(m1[0], m2);
    }
    if (m2.size() == 1) {
        return operator*(m2, m1[0]);
    }
    Matrix matrix(m1.m_row, m2.m_col);
    for(int i=0;i<matrix.m_row;i++) {
        for(int j=0;j<matrix.m_col;j++) {
            double v = 0;
            for(int k=0;k<m1.m_col;k++)
                v += m1.at(i, k) * m2.at(k, j);
            matrix.at(i, j) = v;
        }
    }
    return matrix;
}

Matrix operator/(const Matrix& m1, const Matrix& m2) {
    Matrix matrix = m1;
    matrix /= m2;
    return matrix;
}

Matrix::Matrix(double number) : Matrix(1, 1, &number) {}

Matrix operator+(const Matrix& m) {
    return Matrix(m);
}

Matrix operator-(const Matrix& m) {
    Matrix matrix(m);
    for(int k=0;k<matrix.size();k++) {
        matrix[k] = -matrix[k];
    }
    return matrix;
}

Matrix zeros(int n) {
    return zeros(n, n);
}

Matrix zeros(int row, int col) {
    Matrix matrix(row, col);
    for(int k=0;k<matrix.size();k++) matrix[k] = 0.0;
    return matrix;
}

string Matrix::toString() const {
    if (this->size() == 0) {
        return "!Empty Matrix";
    } else if (this->size() == 1) {
        return to_string(m_array[0]);
    } else {
        string str;
        for(int i=0;i<m_row;i++) {
            for(int j=0;j<m_col;j++) {
                str.append(" ");
                str.append(to_string(at(i, j)));
            }
            str.append("\n");
        }
        return str;
    }
}

Matrix::Matrix() : Matrix(0,0){}

void Matrix::addByAnother(int i, int j, double factor) {
    for(int k=0; k < m_col; k++) {
        at(i, k) += factor * at(j, k);
    }
}

void Matrix::multiplyLine(int i, double factor) {
    for(int k=0; k < m_col; k++) {
        at(i, k) *= factor;
    }
}

void Matrix::swapLine(int i, int j) {
    double tmp;
    for(int k=0; k < m_col; k++) {
        tmp = at(i, k);
        at(i, k) = at(j, k);
        at(j, k) = tmp;
    }
}

void Matrix::upperTriangular() {
    if (size() <= 1) return;
    int k=0;
    for(int j=0;j<m_col;j++) {
        int noneZero = -1;
        for(int i=k;i<m_row;i++) {
            if (!isZero(at(i, j))) {
                noneZero = i;
                break;
            }
        }
        if (noneZero < 0) {
            continue;
        } else {
            if (noneZero != k) addByAnother(k, noneZero);
            for(int i=j+1;i<m_row;i++) {
                addByAnother(i, j, -at(i, j) / at(k, j));
            }
            k++;
        }
    }
}

Matrix Matrix::adjoint() const {
    double d = det();
    if (isZero(d)) {
        Matrix matrix(*this);
        for (int i = 0; i < m_row; i++) {
            for (int j = 0; j < m_col; j++) {
                matrix.at(i, j) = cofactor(i, j).det();
            }
        }
        return matrix;
    } else {
        return d * inverse();
    }
}


double Matrix::det() const {
    Matrix upper = Matrix(*this);
    upper.upperTriangular();
    double result = 1;
    for(int k=0;k<m_row;k++) {
        result *= upper.at(k, k);
    }
    return result;
}

Matrix Matrix::inverse() const{
    Matrix inv = identity(m_row);
    Matrix matrix(*this);
    if (size() < 0) return *this;
    if (size() == 1) {
        matrix[0] = 1 / matrix[0];
        return matrix;
    }
    // upper triangular
    int k=0;
    for(int j=0;j<m_col;j++) {
        int noneZero = -1;
        for(int i=k;i<m_row;i++) {
            if (!isZero(at(i, j))) {
                noneZero = i;
                break;
            }
        }
        if (noneZero < 0) {
            continue;
        } else {
            if (noneZero != k) {
                matrix.addByAnother(k, noneZero);
                inv.addByAnother(k, noneZero);
            }
            for(int i=k+1;i<m_row;i++) {
                double  factor = - matrix.at(i, j) / matrix.at(k, j);
                matrix.addByAnother(i, j, factor);
                inv.addByAnother(i, j, factor);
            }
            k++;
        }
    }
    // check principal diagonal and unitize
    for(int l=0; l < m_row; l++) {
        double d = matrix.at(l, l);
        if (isZero(d)) {
            cerr << "Matrix is not invertible" << endl;
            throw;
        } else {
            double factor = 1/d;
            matrix.multiplyLine(l, factor);
            inv.multiplyLine(l, factor);
        }
    }
    // lower triangular
    for(int j=1;j<m_col;j++) {
        for(int i=0;i<j;i++) {
            double factor = -matrix.at(i, j); // matrix.at(j, j) = 1.0
            matrix.addByAnother(i, j, factor);
            inv.addByAnother(i, j, factor);
        }
    }
    return inv;
}

Matrix Matrix::sub(int row1, int row2, int col1, int col2) const {
    Matrix matrix(row2-row1, col2-col1);
    for(int i=0;i<matrix.m_row;i++) {
        for(int j=0;j<matrix.m_col;j++) {
            matrix.at(i, j) = at(i + row1, j + col1);
        }
    }
    return matrix;
}

int Matrix::rank() const {
    Matrix matrix(*this);
    matrix.upperTriangular();
    int r = m_row;
    int j = m_col - 1;
    for(int i = m_row -1; i >= 0; i--) {
        if (isZero(at(i, j))) {
            r--;
        } else {
            break;
        }
    }
    return r;
}




