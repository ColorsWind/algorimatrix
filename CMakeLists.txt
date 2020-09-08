cmake_minimum_required(VERSION 3.16)
project(algorimatrix)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.14.2\\5.14.2\\msvc2017\\")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5Widgets REQUIRED)

add_executable(algorimatrix
        main.cpp
        Matrix.h
        Matrix.cpp
        Token.cpp Token.h
        TokenStream.cpp
        TokenStream.h
        ExtendParser.cpp
        ExtendParser.h
        MatrixFunc.cpp
        MatrixFunc.h
        ObjectMatrix.h
        MatrixException.cpp
        MatrixException.h
        ParseException.cpp
        ParseException.h
        AlgorimatrixQt.h
        AlgorimatrixQt.cpp
        AlgorimatrixQt.ui
        ParseResult.cpp ParseResult.h)

target_link_libraries(algorimatrix Qt5::Widgets)