cmake_minimum_required(VERSION 3.16)
project(algorimatrix)

set(CMAKE_CXX_STANDARD 11)

add_executable(algorimatrix main.cpp Matrix.h Matrix.cpp Token.cpp Token.h TokenStream.cpp TokenStream.h ExtendParser.cpp ExtendParser.h MatrixFunc.cpp MatrixFunc.h ObjectMatrix.h)