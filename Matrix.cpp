#include "Matrix.h"
#include "MatrixFunc.h"

#include <sstream>




Matrix::Matrix(int row, int col) : ObjectMatrix<double>(row, col) {}

Matrix::Matrix(const Matrix &matrix) = default;

Matrix::Matrix(int row, int col, double *array) : ObjectMatrix<double>(row, col, array) {}

Matrix &Matrix::operator=(const Matrix & m) {
    ObjectMatrix::operator=(m);
    return *this;
}

Matrix &Matrix::operator+=(const Matrix & m) {
    if (m_row != m.m_row || m_col != m.m_col)
        throw MatrixException("The number of rows and cols of two matrices is not equal");
    for (int i = 0; i < size(); i++)
        this->m_array[i] += m.m_array[i];
    return *this;
}

Matrix &Matrix::operator-=(const Matrix & m) {
    if (m_row != m.m_row || m_col != m.m_col)
        throw MatrixException("The number of rows and cols of two matrices is not equal");
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

Matrix Matrix::cofactor(int row, int col) const {
    if (row < 0 || row >= m_row)
        throw MatrixException("Row must be integer 1 to " + to_string(m_row));
    if (col < 0 || col >= m_col)
        throw MatrixException("Col must be integer 1 to " + to_string(m_col));
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
    if (m1.m_col != m2.rows()) {
        throw MatrixException("Matrices cannot be multiplied (op1 is "
            + m1.sizeString() + ", op2 is" + m2.sizeString() + ")");
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

Matrix identity(int n, double factor) {
    if (n < 0)
        throw MatrixException("The order of a square matrix must be a nonnegative number.");
    Matrix matrix = zeros(n);
    for(int k=0;k<n;k++) {
        matrix.at(k, k) = factor;
    }
    return matrix;
}

Matrix zeros(int n) {
    if (n < 0)
        throw MatrixException("The order of a square matrix must be a nonnegative number.");
    return zeros(n, n);
}

Matrix zeros(int row, int col) {
    if (row < 0 || col < 0)
        throw MatrixException("The number of rows and columns of a matrix must be nonnegative");
    Matrix matrix(row, col);
    for(int k=0;k<matrix.size();k++) matrix[k] = 0.0;
    return matrix;
}

Matrix fromBlock(ObjectMatrix<Matrix> block) {
    int totalRow = 0, totalCol = 0; // total;
    int* rows = new int[block.rows()];
    int* cols = new int[block.cols()];
    for(int i=0;i<block.rows();i++) totalRow += rows[i] = block.at(i, 0).rows();
    for(int j=0;j<block.cols();j++) totalCol += cols[j] = block.at(0, j).cols();
    Matrix matrix(totalRow, totalCol);

    int row = 0, col = 0; // line vector index

    // ergodic
    for(int i=0;i<block.rows();i++) {
        for(int j=0;j<block.cols();j++) {
            Matrix &sub = block.at(i, j);
            // check size
            if (rows[i] != sub.rows())
                throw MatrixException("Cannot create matrix from blocks, unexpected matrix size: " + sub.sizeString()
                    + " (Expect row = " + to_string(rows[i]) + ")");
            if (cols[j] != sub.cols())
                throw MatrixException("Cannot create matrix from blocks, unexpected matrix size: " + sub.sizeString()
                    + " (Expect col = " + to_string(cols[j]) + ")");

            for(int k=0;k<sub.rows();k++) {
                copy(sub.m_array + sub.first(k), sub.m_array + sub.first(k+1),
                     matrix.m_array + matrix.first(row + k) + col);
            }
            col += sub.cols();
        }
        row += block.at(i, 0).rows();
        col = 0;
    }
    delete [] rows;
    delete [] cols;

    return matrix;
}

string Matrix::toString() const {
    if (this->size() == 0) {
        return "[]";
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
    if (!square())
        throw MatrixException("Matrix is not a square matrix");
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
    if (!square())
        throw MatrixException("Matrix is not a square matrix");
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
            throw MatrixException("Matrix is not invertible");
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
    // check rows and cols
    if (row1 < 0 || row1 >= m_row) {
        throw MatrixException("Row1 must be integer 1 to " + to_string(m_row));
    }
    if (row1 < 0 || row2 >= m_row) {
        throw MatrixException("Row2 must be integer 1 to " + to_string(m_row));
    }
    if (col1 < 0 || row1 >= m_col) {
        throw MatrixException("Col1 must be integer 1 to " + to_string(m_row));
    }
    if (col2 < 0 || row2 >= m_col) {
        throw MatrixException("Col2 must be integer 1 to " + to_string(m_row));
    }


    // ensure op1 < op2
    if (row1 > row2) {
        int tmp = row2;
        row2 = row1;
        row1 = tmp;
    }
    if (col1 > col2) {
        int tmp = col2;
        col2 = col1;
        col1 = tmp;
    }

    // sub matrix
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

Matrix Matrix::transpose() const {
    Matrix matrix(m_col, m_row);
    for(int i=0;i<m_row;i++) {
        for(int j=0;j<m_col;j++) {
            matrix.at(j, i) = at(i, j);
        }
    }
    return matrix;
}






