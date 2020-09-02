//
// Created by colors_wind on 2020/9/2.
//
#include <cmath>
#include <iostream>
#include "Matrix.h"
#include <map>
using std::map;
using std::string;
const static double PI = acos(-1.0);
const static double E = exp(1.0);

typedef Matrix (*Func1)(Matrix&);
typedef Matrix (*Func2)(Matrix&, Matrix&);

Matrix sin(Matrix&);
Matrix cos(Matrix&);
Matrix tan(Matrix&);
Matrix cot(Matrix&);
Matrix csc(Matrix&);
Matrix sec(Matrix&);
Matrix arcsin(Matrix&);
Matrix arccos(Matrix&);
Matrix arctan(Matrix&);
Matrix ln(Matrix&);
Matrix log(Matrix&, Matrix&);
Matrix exp(Matrix&);
Matrix pow(Matrix&, Matrix&);


map<string, Func1> map_func1 = {
        {"sin", sin},{"cos", cos}, {"tan", tan}, {"cot", cot}, {"csc", csc}, {"sec", sec},
        {"arcsin", arcsin}, {"arccos", arccos}, {"arctan", arctan},
        {"ln", ln}, {"exp", exp}};

map<string, Func2> map_func2 = {
        {{"log", log}, {"pow", pow}}
};


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
