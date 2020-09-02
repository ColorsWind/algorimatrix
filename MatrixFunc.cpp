//
// Created by colors_wind on 2020/9/2.
//
#include "MatrixFunc.h"

Matrix sin(const Matrix &matrix) {
    return matrix.traverse(sin);
}

Matrix cos(const Matrix &matrix) {
    return matrix.traverse(cos);
}

Matrix tan(const Matrix &matrix) {
    return matrix.traverse(tan);
}


Matrix cot(const Matrix &matrix) {
    return matrix.traverse([] (double d)-> double {return tan(PI/2 - d);});
}

Matrix csc(const Matrix &matrix) {
    return matrix.traverse([] (double d)-> double {return 1/sin(d);});
}

Matrix sec(const Matrix &matrix) {
    return matrix.traverse([] (double d)-> double {return 1/cos(d);});
}

Matrix exp(const Matrix &matrix) {
    return matrix.traverse(exp);
}

Matrix pow(const Matrix &base, const Matrix &exponent) {
    return base.traverse(pow, exponent);
}

Matrix ln(const Matrix &matrix) {
    return matrix.traverse(log);
}

Matrix log(const Matrix &base, const Matrix &natural) {
    return  base.traverse([] (double b, double n)-> double {return log(n) / log(b);}, natural);
}

Matrix arcsin(const Matrix &matrix) {
    return  matrix.traverse(asin);
}

Matrix arccos(const Matrix &matrix) {
    return matrix.traverse(acos);
}

Matrix arctan(const Matrix &matrix) {
    return matrix.traverse(atan);
}

map<string, Func1> map_func1 = {
        {"sin", sin},{"cos", cos}, {"tan", tan}, {"cot", cot}, {"csc", csc}, {"sec", sec},
        {"arcsin", arcsin}, {"arccos", arccos}, {"arctan", arctan},
        {"ln", ln}, {"exp", exp}};

map<string, Func2> map_func2 = {
        {{"log", log}, {"pow", pow}}
};