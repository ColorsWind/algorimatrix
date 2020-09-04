//
// Created by colors_wind on 2020/9/2.
//
#include "MatrixFunc.h"


bool isZero(double d) {
    return abs(d) < EPS;
}


Matrix sin(const vector<Matrix> &matrix) {
        return matrix[0].traverse(sin);
}

Matrix cos(const vector<Matrix> &matrix) {
    return matrix[0].traverse(cos);
}

Matrix tan(const vector<Matrix> &matrix) {
    return matrix[0].traverse(tan);
}


Matrix cot(const vector<Matrix> &matrix) {
    return matrix[0].traverse([] (double d)-> double {return tan(PI/2 - d);});
}

Matrix csc(const vector<Matrix> &matrix) {
    return matrix[0].traverse([] (double d)-> double {return 1/sin(d);});
}

Matrix sec(const vector<Matrix> &matrix) {
    return matrix[0].traverse([] (double d)-> double {return 1/cos(d);});
}

Matrix exp(const vector<Matrix> &matrix) {
    return matrix[0].traverse(exp);
}

/**
 * matrix[0] base
 * matrix[1] exponent
 * @param matrix
 * @return
 */
Matrix pow(const vector<Matrix> &matrix) {
    return matrix[0].traverse(pow, matrix[1]);
}

Matrix ln(const vector<Matrix> &matrix) {
    return matrix[0].traverse(log);
}

/**
 * matrix[0] base
 * matrix[1] natural
 * @param matrix
 * @return
 */
Matrix log(const vector<Matrix> &matrix) {
    return  matrix[0].traverse([] (double b, double n)-> double {return log(n) / log(b);}, matrix[1]);
}

Matrix arcsin(const vector<Matrix> &matrix) {
    return  matrix[0].traverse(asin);
}

Matrix arccos(const vector<Matrix> &matrix) {
    return matrix[0].traverse(acos);
}

Matrix arctan(const vector<Matrix> &matrix) {
    return matrix[0].traverse(atan);
}
Matrix triu(const vector<Matrix> &matrix) {
    Matrix upper(matrix[0]);
    upper.upperTriangular();
    return upper;
}


Matrix det(const vector<Matrix> &matrix) {
    return Matrix(matrix[0].det());
}

Matrix inverse(const vector<Matrix> &matrix) {
    return matrix[0].inverse();
}

Matrix size(const vector<Matrix> &matrix) {
    Matrix m(1, 2);
    m[0] = matrix[0].rows();
    m[1] = matrix[1].cols();
    return m;
}

Matrix sub(const vector<Matrix> &matrix) {
    return matrix[0].sub((int)matrix[1][0]-1, (int)matrix[2][0], (int)matrix[3][0]-1, (int)matrix[4][0]);
}



Matrix zeros(const vector<Matrix> &matrix) {
    if (matrix.size() == 1) {
        Matrix sizeM = matrix[0];
        if (sizeM.size() == 1) {
            return zeros(sizeM[0]);
        } else if (sizeM.size() == 2) {
            return zeros(sizeM[0], sizeM[1]);
        }
    } else if (matrix.size() == 2) {
        return zeros(matrix[0][0], matrix[1][0]);
    }
    throw;
}

Matrix ident(const vector<Matrix> &matrix) {
    if (matrix.size() == 1) {
        return identity(matrix[0][0]);
    } else if (matrix.size() == 2) {
        return identity(matrix[0][0], matrix[1][0]);
    }
    throw;
}

Matrix row(const vector<Matrix> &matrix) {
    return Matrix(matrix[0].rows());
}

Matrix col(const vector<Matrix> &matrix) {
    return Matrix(matrix[1].cols());
}


Matrix swap(const vector<Matrix> &matrix) {
    Matrix result(matrix[0]);
    result.swapLine((int)matrix[1][0]-1, (int)matrix[2][1]-1);
    return result;
}

Matrix add(const vector<Matrix> &matrix) {
    Matrix result(matrix[0]);
    if (matrix.size() == 3) {
        result.addByAnother((int)matrix[1][0]-1, (int)matrix[2][0]-1);
    } else if (matrix.size() == 4) {
        result.addByAnother((int)matrix[1][0]-1, (int)matrix[2][0]-1, (int)matrix[3][0]);
    } else {
        throw;
    }
    return result;
}

Matrix multiply(const vector<Matrix> &matrix) {
    Matrix result(matrix[0]);
    result.multiplyLine((int)matrix[1][0] -1, (int)matrix[2][0]);
    return result;
}

Matrix adjoint(const vector<Matrix> &matrix) {
    return matrix[0].adjoint();
}

Matrix cofactor(const vector<Matrix> &matrix) {
    return matrix[0].cofactor((int)matrix[1][0], (int)matrix[2][0]);
}

Matrix rank(const vector<Matrix> &matrix) {
    return Matrix(matrix[0].rank());
}


map<string, Func> map_func = {
        {"sin", sin},{"cos", cos}, {"tan", tan}, {"cot", cot},
        {"csc", csc}, {"sec", sec},
        {"arcsin", arcsin}, {"arccos", arccos}, {"arctan", arctan},
        {"ln", ln}, {"log", log}, {"exp", exp}, {"pow", pow},
        {"triu", triu}, {"det", det}, {"inv", inverse},
        {"swap", swap}, {"add", add}, {"multiply", multiply},
        {"sub", sub}, {"zeros", zeros}, {"ident", ident},
        {"adjoint", adjoint}, {"cofactor", cofactor},
        {"size", size}, {"row", row}, {"col", col}, {"rank", rank}
};









