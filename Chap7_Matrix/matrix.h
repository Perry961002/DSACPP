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
    friend ostream& operator<<(ostream& out, const matrix<T>& m) {
        for (int i = 0; i < m.theRows; ++i) {
            for (int j = 0; j < m.theColumns; ++j) {
                out << m.element[i * m.theColumns + j] << " ";
            }
            out << endl;
        }
        return out;
    }
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
    matrix<T> operator*(const matrix<T>&) const;

    // 重载+=，-=，*=，/=运算符
    matrix<T>& operator+=(const T&);
    matrix<T>& operator-=(const T&);
    matrix<T>& operator*=(const T&);
    matrix<T>& operator/=(const T&);

    // 矩阵转置
    matrix<T> tranpose() const;

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
    theColumns = m.theColumns;
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
    if (i < 1 || i > theRows || j < 1 || j > theColumns)
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

// 一元+运算符
template <class T>
matrix<T> matrix<T>::operator+() const {
    matrix<T> m(theRows, theColumns);
    for(int i = 0; i < theRows * theColumns; ++i)
        m.element[i] = +element[i];
    return m;
}

// 重载+=运算符
template <class T>
matrix<T>& matrix<T>::operator+=(const T &x) {
    for(int i = 0; i < theRows * theColumns; ++i)
        element[i] += x;
    return *this;
}

// 重载-运算符，矩阵减法
template <class T>
matrix<T> matrix<T>::operator-(const matrix<T> &m) const {
    // 只有行列数相同的矩阵才能相加
    if (theRows != m.theRows || theColumns != m.theColumns)
        throw matrixIndexOutOfBounds();

    // 生成结果矩阵
    matrix<T> w(theRows, theColumns);
    for(int i = 0; i < theRows * theColumns; ++i)
        w.element[i] = element[i] - m.element[i];

    return w;
}

// 一元-运算符
template <class T>
matrix<T> matrix<T>::operator-() const {
    matrix<T> m(theRows, theColumns);
    for(int i = 0; i < theRows * theColumns; ++i)
        m.element[i] = -element[i];
    return m;
}

// 重载-=运算符
template <class T>
matrix<T>& matrix<T>::operator-=(const T &x) {
    for(int i = 0; i < theRows * theColumns; ++i)
        element[i] -= x;
    return *this;
}

// 重载*运算符，矩阵乘法
template <class T>
matrix<T> matrix<T>::operator*(const matrix<T> &m) const {
    // 要求*this的列数等于m的行数
    if (theColumns != m.theRows)
        throw matrixIndexOutOfBounds();

    matrix<T> w(theRows, m.theColumns);  // 结果矩阵

    // 矩阵*this，m和w的游标且初始化为(1, 1)元素定位
    int ct = 0, cm = 0, cw = 0;

    //对所有i和j计算 w(i, j)
    for(int i = 1; i <= theRows; ++i) {
        // 计算结果的第i行
        for(int j = 1; j <= m.theColumns; ++j) {
            // 计算w(i, j)
            T sum = element[ct] * m.element[cm];

            // 累加其他剩余项
            for(int k = 2; k <= theColumns; ++k) {
                ++ct;  // *this第i行的下一项
                cm += m.theColumns;  // m第j列的下一项
                sum += element[ct] * element[cm];
            }
            w.element[cw++] = sum;

            // 从行的起点和下一列重新开始
            ct -= theColumns - 1;
            cm = j;
        }

        //从下一行和第一列开始
        ct += theColumns;
        cm = 0;
    }
    return w;
}

// 重载*=运算符
template <class T>
matrix<T>& matrix<T>::operator*=(const T &x) {
    for(int i = 0; i < theRows * theColumns; ++i)
        element[i] *= x;
    return *this;
}

// 重载/=运算符
template <class T>
matrix<T>& matrix<T>::operator/=(const T &x) {
    for(int i = 0; i < theRows * theColumns; ++i)
        element[i] /= x;
    return *this;
}

// 矩阵转置
template <class T>
matrix<T> matrix<T>::tranpose() const {
    // 生成结果矩阵
    matrix<T> m(theColumns, theRows);

    // *this的(i, j)索引上的元素是 m 的(j, i)索引上的元素
    for (int it = 0; it < theRows * theColumns; ++it) {
        int i = it / theColumns;
        int j = it % theColumns;
        m.element[j * theRows + i] = element[it];
    }
    return m;
}

#endif //DSACPP_MATRIX_H
