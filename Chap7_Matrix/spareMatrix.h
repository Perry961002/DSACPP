//
// Created by perry on 2019/10/31.
//

#ifndef DSACPP_SPAREMATRIX_H
#define DSACPP_SPAREMATRIX_H

#include "../MyExceptions.h"
#include "../Chap5_ArrayList/arrayList.h"

//按行主次序，记录每个非零元素的行号、列号和值
template <class T>
struct matrixTerm {
    int row, col;  //行号和列号
    T value;  //元素值
    matrixTerm(int r, int c, const T& v): row(r), col(c), value(v) {}
};

//稀疏矩阵类
template <class T>
class spareMatrix {
    //重载输入、输出运算符
    friend ostream& operator<<(ostream& out, const spareMatrix<T>& x);
    friend istream& operator>>(istream& in, spareMatrix<T>& x);
public:
    void transpose(spareMatrix<T> &b);
    void add(spareMatrix<T> &b, spareMatrix<T> &c);
private:
    int rows, cols;  //矩阵行数和列数
    arrayList<matrixTerm<T>> terms;  //非0项表
};

//重载<<运算符
template <class T>
ostream& operator<<(ostream& out, const spareMatrix<T>& x) {
    //输出矩阵特征
    out << "rows = " << x.rows << "columns = " << x.cols << endl;
    out << "nonzero terms = " << x.terms.size() << endl;

    //输出矩阵项
    for(typename arrayList<spareMatrix<T> >::iterator i = x.terms.begin();
        i != x.terms.end(); ++i)
        out << "a(" << (*i).row << ',' << (*i).col << ") = " << (*i).value << endl;
    return out;
}

//重载>>运算符
template <class T>
istream& operator>>(istream& in, spareMatrix<T>& x) {
    //输入矩阵特征
    int theRows, theColumns, numberOfTerms;
    cout << "Enter number of rows, columns, and #terms" << endl;
    in >> theRows >> theColumns >> numberOfTerms;

    //检查输入合法性
    if (theRows < 0 || theColumns < 0)
        throw illegalParameterValue("Rows and Columns must be >= 0");
    if ((theRows ==0 || theColumns == 0) && (theRows != 0 || theColumns != 0))
        throw illegalParameterValue("Either both or neither rows and columns should be zero");
    if (numberOfTerms >= (theRows * theColumns / 3))
        throw illegalParameterValue("number of term must be < (rows * columns / 3)");

    //设置x.terms的大小，确保足够的容量
    x.terms.reSet(numberOfTerms);

    //输入项
    matrixTerm<T> mTerms;
    for(int i = 0; i < numberOfTerms; ++i) {
        cout << "Enter row, columns, and value of term " << (i + 1) << endl;
        in >> mTerms.row >> mTerms.col >> mTerms.value;

        //检查输入合法性
        if (mTerms.row < 1 || mTerms.row > x.rows)
            throw illegalParameterValue("row must be >= 1 and <= matrix.rows");
        if (mTerms.col < 1 || mTerms.col > x.cols)
            throw illegalParameterValue("col must be >= 1 and <= matrix.cols");
        if (mTerms.row < x.terms[i - 1].row ||
            (mTerms.row == x.terms[i - 1].row && mTerms.col <= x.terms[i - 1].col))
            throw illegalParameterValue("Please enter in line main order");
        if (mTerms.value == 0)
            throw illegalParameterValue("value of term must be != 0");
        x.terms.set(i, mTerms);
    }
    return in;
}

//矩阵转置
template <class T>
void spareMatrix<T>::transpose(spareMatrix<T> &b) {
    //设置转置矩阵特征
    b.cols = rows;
    b.rows = cols;
    b.terms.reSet(terms.size());

    int *colSize = new int[cols + 1];  //*this的每一列的项的数目
    int *rowNext = new int[cols + 1];  //b中每一行的起始项在terms中的位置

    for (int i = 1; i <= cols; ++i)
        colSize[i] = 0;
    for (typename arrayList<matrixTerm<T>>::iterator i = terms.begin(); i != terms.end(); ++i)
        ++colSize[(*i).col];

    rowNext[1] = 0;
    for (int i = 2; i <= cols; ++i)
        rowNext[i] = rowNext[i - 1] + colSize[i - 1];

    //开始转置
    matrixTerm<T> mTerms;
    for (typename arrayList<matrixTerm<T>>::iterator i = terms.begin(); i != terms.end(); ++i) {
        int j = rowNext[(*i).col]++;  //在b的terms中的位置
        mTerms.row = (*i).col;
        mTerms.col = (*i).row;
        mTerms.value = (*i).value;
        b.terms.set(j, mTerms);
    }
}

//矩阵相加
template <class T>
void spareMatrix<T>::add(spareMatrix<T> &b, spareMatrix<T> &c) {
    //计算c = (*this) + b

    //检验相容性
    if (rows != b.rows || cols != b.cols)
        throw matrixSizeMismatch();
    //设置结果矩阵c的特征
    c.rows = rows;
    c.cols = cols;
    c.terms.clear();
    int cSize = 0;

    //定义*this和b的迭代器
    typename arrayList<matrixTerm<T>>::iterator it = terms.begin();
    typename arrayList<matrixTerm<T>>::iterator ib = b.terms.begin();
    typename arrayList<matrixTerm<T>>::iterator itEnd = terms.end();
    typename arrayList<matrixTerm<T>>::iterator ibEnd = b.terms.end();

    //遍历*this和b，把相关的项相加
    while (it != itEnd && ib != ibEnd) {
        //行主索引加上每一项的列数
        int tIndex = (*it).row * cols + (*it).col;
        int bIndex = (*ib).row * cols + (*ib).col;

        if (tIndex < bIndex) {
            //b项在后
            c.terms.insert(cSize++, *it);
            ++it;
        } else if (tIndex == bIndex) {
            //同一位置
            if ((*it).value + (*ib).value != 0) {
                //两项和不为0时加入c
                c.terms.insert(cSize++, matrixTerm<T>((*it).row, (*it).col, (*it).value + (*ib).value));
            }
            ++it;
            ++ib;
        } else {
            //*this在后
            c.terms.insert(cSize++, *ib);
            ++ib;
        }
    }

    //复制剩余项
    while (it != itEnd)
        c.terms.insert(cSize++, *(it++));
    while (ib != ibEnd)
        c.terms.insert(cSize++, *(ib++));
}

#endif //DSACPP_SPAREMATRIX_H
