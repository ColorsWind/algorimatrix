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

extern map<string, Func1> map_func1;
extern map<string, Func2> map_func2;


#endif //ALGORIMATRIX_MATRIXFUNC_H
