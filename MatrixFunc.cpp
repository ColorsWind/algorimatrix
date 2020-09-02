//
// Created by colors_wind on 2020/9/2.
//
#include "MatrixFunc.h"

Matrix sin(Matrix &matrix) {
    return matrix.traverse(sin);
}

Matrix cos(Matrix &matrix) {
    return matrix.traverse(cos);
}

Matrix tan(Matrix &matrix) {
    return matrix.traverse(tan);
}


Matrix cot(Matrix &matrix) {
    return matrix.traverse([] (double d)-> double {return tan(PI/2 - d);});
}

Matrix csc(Matrix &matrix) {
    return matrix.traverse([] (double d)-> double {return 1/sin(d);});
}

Matrix sec(Matrix &matrix) {
    return matrix.traverse([] (double d)-> double {return 1/cos(d);});
}

Matrix exp(Matrix &matrix) {
    return matrix.traverse(exp);
}

Matrix pow(Matrix &base, Matrix &exponent) {
    return base.traverse(pow, exponent);
}

Matrix ln(Matrix &matrix) {
    return matrix.traverse(log);
}

Matrix log(Matrix &base, Matrix &natural) {
    return  base.traverse([] (double b, double n)-> double {return log(n) / log(b);}, natural);
}

Matrix arcsin(Matrix &matrix) {
    return  matrix.traverse(asin);
}

Matrix arccos(Matrix &matrix) {
    return matrix.traverse(acos);
}

Matrix arctan(Matrix &matrix) {
    return matrix.traverse(atan);
}

map<string, Func1> map_func1 = {
        {"sin", sin},{"cos", cos}, {"tan", tan}, {"cot", cot}, {"csc", csc}, {"sec", sec},
        {"arcsin", arcsin}, {"arccos", arccos}, {"arctan", arctan},
        {"ln", ln}, {"exp", exp}};

map<string, Func2> map_func2 = {
        {{"log", log}, {"pow", pow}}
};