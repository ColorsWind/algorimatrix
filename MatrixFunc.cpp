//
// Created by colors_wind on 2020/9/2.
//
#include "MatrixFunc.h"

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

map<string, Func> map_func = {
        {"sin", sin},{"cos", cos}, {"tan", tan}, {"cot", cot}, {"csc", csc}, {"sec", sec},
        {"arcsin", arcsin}, {"arccos", arccos}, {"arctan", arctan},
        {"ln", ln}, {"log", log}, {"exp", exp}, {"pow", pow}};
