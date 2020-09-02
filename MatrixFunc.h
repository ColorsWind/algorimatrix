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

extern map<string, Func> map_func;

#endif //ALGORIMATRIX_MATRIXFUNC_H
