//
// Created by colors_wind on 2020/9/3.
//

#ifndef ALGORIMATRIX_OBJECTMATRIX_H
#define ALGORIMATRIX_OBJECTMATRIX_H
#include <iostream>
#include <vector>


using std::vector;

template <typename Object>
class ObjectMatrix {
protected:
    int m_row;
    int m_col;
    Object *m_array;
public:
    ~ObjectMatrix ();
    ObjectMatrix();
    explicit ObjectMatrix(vector<vector<Object>> &array);
    ObjectMatrix(const ObjectMatrix &matrix);
    ObjectMatrix(int row, int col);
    ObjectMatrix(int row, int col, Object *array);

    ObjectMatrix & operator=(const ObjectMatrix & m);
    Object & operator[](int k);
    Object & operator[](int k) const;


    inline int rows() const;

    inline int cols() const;

    inline int size() const;

    inline int first(int row) const;
    inline Object & at(int row, int col);
    inline const Object & at(int row, int col) const;

    void swapRow(int i, int j);
    void swapCol(int i, int j);
};


template<typename Object>
ObjectMatrix<Object>::~ObjectMatrix() {
    delete [] m_array;
    m_array = nullptr;
}

template<typename Object>
ObjectMatrix<Object>::ObjectMatrix() : ObjectMatrix(0,0) {}

template<typename Object>
ObjectMatrix<Object>::ObjectMatrix(int row, int col) : m_row(row), m_col(col) {
    m_array = new Object[size()];
}

template<typename Object>
ObjectMatrix<Object>::ObjectMatrix(const ObjectMatrix &matrix) : ObjectMatrix(matrix.m_row, matrix.m_col) {
    copy(matrix.m_array, matrix.m_array + size(), m_array);
}

template<typename Object>
ObjectMatrix<Object>::ObjectMatrix(int row, int col, Object *array) : ObjectMatrix(row, col) {
    copy(array, array + size(), m_array);
}

template<typename Object>
ObjectMatrix<Object> &ObjectMatrix<Object>::operator=(const ObjectMatrix &m) {
    if (size() != m.size()) {
        delete [] m_array;
        m_array = new Object[m.size()];
    }
    m_col = m.m_col;
    m_row = m.m_row;
    copy(m.m_array, m.m_array + size(), m_array);
    return *this;
}

template<typename Object>
Object &ObjectMatrix<Object>::operator[](int k) {
    return m_array[k];
}

template<typename Object>
Object &ObjectMatrix<Object>::operator[](int k) const {
    return m_array[k];
}


template<typename Object>
int ObjectMatrix<Object>::rows() const {
    return m_row;
}

template<typename Object>
int ObjectMatrix<Object>::cols() const {
    return m_col;
}

template<typename Object>
int ObjectMatrix<Object>::size() const {
    return m_row * m_col;
}

template<typename Object>
int ObjectMatrix<Object>::first(int row) const {
    return m_col * row;
}

template<typename Object>
Object &ObjectMatrix<Object>::at(int row, int col) {
    return m_array[first(row) + col];
}

template<typename Object>
const Object &ObjectMatrix<Object>::at(int row, int col) const {
    return m_array[first(row) + col];
}

template<typename Object>
void ObjectMatrix<Object>::swapRow(int i, int j) {
    Object* tmp;
    int iFirst = first(i);
    int jFirst = first(j);
    for(int k=0;k<m_col;k++) {
        tmp = &m_array[iFirst + k];
        m_array[iFirst + k] = m_array[jFirst + k];
        m_array[jFirst + k] = *tmp;
    }
}

template<typename Object>
void ObjectMatrix<Object>::swapCol(int i, int j) {
    Object* tmp;
    for(int k=0;k<m_col;k++) {
        tmp = &m_array[first(k) + i];
        m_array[first(k) + i] = m_array[first(k) + j];
        m_array[first(k) + j] = *tmp;
    }
}

template<typename Object>
ObjectMatrix<Object>::ObjectMatrix(vector<vector<Object>> &array) {
    m_row = array.size();
    m_col = array[0].size();
    m_array = new Object[m_row * m_col];
    for(int k=0;k<m_row;k++) {
        vector<Object> &sub = array[k];
        copy(sub.begin(), sub.end(), m_array + first(k));
    }
}


#endif ALGORIMATRIX_OBJECTMATRIX_H
