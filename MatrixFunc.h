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

Matrix sin(const Matrix&);
Matrix cos(const Matrix&);
Matrix tan(const Matrix&);
Matrix cot(const Matrix&);
Matrix csc(const Matrix&);
Matrix sec(const Matrix&);
Matrix arcsin(const Matrix&);
Matrix arccos(const Matrix&);
Matrix arctan(const Matrix&);
Matrix ln(const Matrix&);
Matrix log(const Matrix&, const Matrix&);
Matrix exp(const Matrix&);
Matrix pow(const Matrix&, const Matrix&);

extern map<string, Func1> map_func1;
extern map<string, Func2> map_func2;


#endif //ALGORIMATRIX_MATRIXFUNC_H
