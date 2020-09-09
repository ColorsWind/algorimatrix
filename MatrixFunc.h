//
// Created by colors_wind on 2020/9/2.
//

#ifndef ALGORIMATRIX_MATRIXFUNC_H
#define ALGORIMATRIX_MATRIXFUNC_H

#include "Matrix.h"
#include <cmath>
#include <map>
using std::map;

const static double PI = acos(-1.0);
const static double E = exp(1.0);
const static double EPS = 10E-5;
bool isZero(double d);

Matrix sin(const vector<Matrix>&);
Matrix cos(const vector<Matrix>&);
Matrix tan(const vector<Matrix>&);
Matrix cot(const vector<Matrix>&);
Matrix csc(const vector<Matrix>&);
Matrix sec(const vector<Matrix>&);
Matrix arcsin(const vector<Matrix>&);
Matrix arccos(const vector<Matrix>&);
Matrix arctan(const vector<Matrix>&);
Matrix ln(const vector<Matrix>&);
Matrix log(const vector<Matrix>&);
Matrix exp(const vector<Matrix>&);
Matrix pow(const vector<Matrix>&);

Matrix triu(const vector<Matrix>&);
Matrix det(const vector<Matrix>&);
Matrix inverse(const vector<Matrix> &matrix);
Matrix swap(const vector<Matrix> &matrix);
Matrix add(const vector<Matrix> &matrix);
Matrix multiply(const vector<Matrix> &matrix);


Matrix sub(const vector<Matrix> &matrix);
Matrix zeros(const vector<Matrix> &matrix);
Matrix ident(const vector<Matrix> &matrix);

Matrix adjoint(const vector<Matrix> &matrix);
Matrix cofactor(const vector<Matrix> &matrix);

Matrix size(const vector<Matrix> &matrix);
Matrix row(const vector<Matrix> &matrix);
Matrix col(const vector<Matrix> &matrix);
Matrix rank(const vector<Matrix> &matrix);

Matrix reshape(const vector<Matrix> &matrix);
Matrix trans(const vector<Matrix> &matrix);

Matrix sleep(const vector<Matrix> &matrix);

extern map<string, Func> map_func;

#endif //ALGORIMATRIX_MATRIXFUNC_H
