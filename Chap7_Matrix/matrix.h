//
// Created by perry on 2019/10/24.
//

#ifndef DSACPP_MATRIX_H
#define DSACPP_MATRIX_H

#include <ostream>
#include "../MyExceptions.h"

//矩阵类
template <class T>
class matrix {
    // 友元函数，重载的<<
    friend ostream& operator<<(ostream&, const matrix);
public:
    //构造函数、复制构造函数和析构函数
    matrix(int theRows = 0, int theColums = 0);
    matrix(const matrix<T>&);
    ~matrix() {delete [] element;}

    // 获取行数和列数
    int rows() const {return theRows;}
    int columns() const {return theColumns;}

    // 重载()，可以像数学表达式一样访问元素
    T& operator() (int i, int j) const;

    // 重载=运算符
    matrix<T>& operator=(const matrix<T>&);

    // 一元和二元的+运算符
    matrix<T> operator+() const;
    matrix<T> operator+(const matrix<T>&) const;

    // 一元和二元的-运算符
    matrix<T> operator-() const;
    matrix<T> operator-(const matrix<T>&) const;

    // 重载*运算符
    matrix<T> operator*() const;

    // 重载+=运算符
    matrix<T>& operator+=(const T&);

private:
    int theRows, theColumns;  //矩阵的行数和列数
    T *element;  // 数组 element
};

// 构造函数和复制构造函数
template <class T>
matrix<T>::matrix(int theRows, int theColums) {
    // 检查参数的有效性，可以生成行数和列数都大于0的矩阵，也可以生成0*0的矩阵
    if (theRows < 0 || theColums < 0)
        throw illegalParameterValue("Rows and Columns must be >= 0");
    if ((theRows ==0 || theColums == 0) && (theRows != 0 || theColums != 0))
        throw illegalParameterValue("Either both or neither rows and columns should be zero");

    // 创建行主映射矩阵
    this->theRows = theRows;
    this->theColumns = theColums;
    this->element = new T [theRows * theColums];
}

template <class T>
matrix<T>::matrix(const matrix<T>& m) {
    // 创建矩阵
    theRows = m.theRows;
    theColumns = m.theColums;
    element = new T [theRows * theColumns];

    // 复制所有元素
    copy(m.element, m.element + theRows * theColumns, element);
}

// 重载=运算符
template <class T>
matrix<T>& matrix<T>::operator=(const matrix<T>& m) {
    // 不能赋值给自己
    if (this != &m) {
        // 先清空，再复制
        delete [] element;
        theRows = m.theRows;
        theColumns = m.theColumns;
        element = new T [theRows * theColumns];
        copy(m.element, m.element + theRows * theColumns, element);
    }
    return *this;
}

// 重载()运算符，满足数学表达式一样的访问
template <class T>
T& matrix<T>::operator()(int i, int j) const {
    // 检查索引是否有效
    if (i < 1 || i > theRows || j < 1 || j < theColumns)
        throw matrixIndexOutOfBounds();
    return element[(i - 1) * theColumns + j - 1];
}

// 重载+运算符，矩阵加法
template <class T>
matrix<T> matrix<T>::operator+(const matrix<T> &m) const {
    // 只有行列数相同的矩阵才能相加
    if (theRows != m.theRows || theColumns != m.theColumns)
        throw matrixIndexOutOfBounds();

    // 生成结果矩阵
    matrix<T> w(theRows, theColumns);
    for(int i = 0; i < theRows * theColumns; ++i)
        w.element[i] = element[i] + m.element[i];

    return w;
}

// 重载*运算符，矩阵乘法


#endif //DSACPP_MATRIX_H
