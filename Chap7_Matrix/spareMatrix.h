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
    matrixTerm() : row(0), col(0), value(0) {}
    matrixTerm(int r, int c, const T& v): row(r), col(c), value(v) {}
    operator T() const {return value;}
};

template <class T> class spareMatrix;
template <class T> istream& operator>>(istream& in, spareMatrix<T>& x);
template <class T> ostream& operator<<(ostream& out, spareMatrix<T>& x);

//稀疏矩阵类
template <class T>
class spareMatrix {
    //重载输入、输出运算符
    friend ostream& operator<< <>(ostream& out, spareMatrix<T>& x);
    friend istream& operator>> <>(istream& in, spareMatrix<T>& x);
public:
    //构造函数和复制构造函数
    spareMatrix() {}
    spareMatrix(const spareMatrix<T>& m);

    //get和set方法
    T& get(int theRow, int theColumn) const;
    void set(int theRow, int theColumn, const T& theValue);

    //转置
    void transpose(spareMatrix<T> &b);

    //加法
    void add(spareMatrix<T> &b, spareMatrix<T> &c);

    //乘法
    void multiply(spareMatrix<T> &b, spareMatrix<T> &c);
private:
    int rows, cols;  //矩阵行数和列数
    arrayList<matrixTerm<T> > terms;  //非0项表
};

//重载<<运算符
template <class T>
ostream& operator<<(ostream& out, spareMatrix<T>& x) {
    //输出矩阵特征
    out << "rows = " << x.rows << "columns = " << x.cols << endl;
    out << "nonzero terms = " << x.terms.size() << endl;

    //输出矩阵项
    for(auto i = x.terms.begin(); i != x.terms.end(); ++i)
        out << "a(" << (*i).row << ',' << (*i).col << ") = " << (*i).value << endl;
    return out;
}

//重载>>运算符
template <class T>
istream& operator>>(istream& in, spareMatrix<T>& x) {
    //输入矩阵特征
    int numberOfTerms;
    cout << "Enter number of rows, columns, and #terms" << endl;
    in >> x.rows >> x.cols >> numberOfTerms;

    //检查输入合法性
    if (x.rows < 0 || x.cols < 0)
        throw illegalParameterValue("Rows and Columns must be >= 0");
    if ((x.rows ==0 || x.cols == 0) && (x.rows != 0 || x.cols != 0))
        throw illegalParameterValue("Either both or neither rows and columns should be zero");
    if (numberOfTerms >= (x.rows * x.cols / 3))
        throw illegalParameterValue("number of term must be < (rows * columns / 3)");

    //设置x.terms的大小，确保足够的容量
    x.terms.reSet(numberOfTerms);

    //输入项
    matrixTerm<T> mTerms;
    for(int i = 0; i < numberOfTerms; ++i) {
        cout << "Enter row, columns, and value of term " << (i + 1) << endl;
        in >> mTerms.row >> mTerms.col >> mTerms.value;

        //检查输入合法性
        if (mTerms.row < 1 || mTerms.row > x.rows || mTerms.col < 1 || mTerms.col > x.cols)
            throw matrixIndexOutOfBounds();
        if (i >= 1 && (mTerms.row < x.terms[i - 1].row ||
            (mTerms.row == x.terms[i - 1].row && mTerms.col <= x.terms[i - 1].col)))
            throw illegalParameterValue("Please enter in line main order");
        if (mTerms.value == 0)
            throw illegalParameterValue("value of term must be != 0");
        x.terms.set(i, mTerms);
    }
    return in;
}

//复制构造函数
template <class T>
spareMatrix<T>::spareMatrix(const spareMatrix<T> &m) {
    rows = m.rows;
    cols = m.cols;
    terms = arrayList<matrixTerm<T>>(m.terms);
}

//get方法
template <class T>
T & spareMatrix<T>::get(int theRow, int theColumn) const {
    //检查索引是否有效
    if (theRow < 1 || theRow > rows || theColumn < 1 || theColumn > cols)
        throw matrixIndexOutOfBounds();

    //找到第一个不在所给索引之前的非0元素
    auto i = terms.begin();
    while (i != terms.end() && !((*i).row >= theRow && (*i).col >= theColumn))
        ++i;

    //所给索引位置的元素是非0的
    if ((*i).row == theRow && (*i).col == theColumn)
        return (*i).value;
    else
        return 0;
}

//set方法
template <class T>
void spareMatrix<T>::set(int theRow, int theColumn, const T &theValue) {
    //检查索引是否有效
    if (theRow < 1 || theRow > rows || theColumn < 1 || theColumn > cols)
        throw matrixIndexOutOfBounds();

    //找到第一个不在所给索引之前的非0元素
    auto i = terms.begin();
    while (i != terms.end() && !((*i).row >= theRow && (*i).col >= theColumn))
        ++i;

    //所给索引位置的元素是非0的
    if ((*i).row == theRow && (*i).col == theColumn) {
        //theValue非0
        if(theValue != 0)
            (*i).value = theValue;
        else
            //设为0，需要删除
            terms.erase(i - terms.begin());
    } else if (theValue != 0)
        //插入新的非0元素
        terms.insert(i - terms.begin(), matrixTerm<T>(theRow, theColumn, theValue));
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
    for (auto i = terms.begin(); i != terms.end(); ++i)
        ++colSize[(*i).col];

    rowNext[1] = 0;
    for (int i = 2; i <= cols; ++i)
        rowNext[i] = rowNext[i - 1] + colSize[i - 1];

    //开始转置
    matrixTerm<T> mTerms;
    for (auto i = terms.begin(); i != terms.end(); ++i) {
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
    auto it = terms.begin();
    auto ib = b.terms.begin();
    auto itEnd = terms.end();
    auto ibEnd = b.terms.end();

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

//乘法
template <class T>
void spareMatrix<T>::multiply(spareMatrix<T> &b, spareMatrix<T> &c) {
    //计算c = (*this) * b
    //检验相容性
    if (cols != b.rows)
        throw matrixSizeMismatch();
    //设置结果矩阵c的特征
    c.rows = rows; c.cols = b.cols; c.terms.clear();
    int cSize = 0;

    //将b转置
    spareMatrix<T> d;
    b.transpose(d);

    //统计*this和d的每一行的非0元素个数
    int *rowSizeA = new int[rows + 1], *rowNext = new int[rows + 1];
    for (int i = 1; i <= rows; ++i) rowSizeA[i] = 0;
    for (auto i = terms.begin(); i != terms.end(); ++i) ++rowSizeA[(*i).row];
    //*this每行开始的位置
    rowNext[1] = 0;
    for (int i = 2; i <= cols; ++i)
        rowNext[i] = rowNext[i - 1] + rowSizeA[i - 1];

    int *rowSizeD = new int[d.rows + 1];
    for (int i = 1; i <= d.rows; ++i) rowSizeD[i] = 0;
    for (auto i = d.terms.begin(); i != d.terms.end(); ++i) ++rowSizeD[(*i).row];

    //*this的每一行和d的每一行做内积
    auto it = terms.begin(), id = d.terms.begin();
    for (int i = 1; i <= rows; ++i) {
        id = d.terms.begin();
        for (int j = 1; j <= d.rows; ++j) {
            if (rowSizeA[i] != 0 && rowSizeD[j] != 0) {
                it = terms.begin() + rowNext[i];
                int sum = 0, rA = rowSizeA[i], rD = rowSizeD[j];
                while (rA != 0 && rD != 0) {
                    if ((*it).col < (*id).col) {
                        ++it; --rA;
                    } else if ((*it).col > (*id).col) {
                        ++id; --rD;
                    } else {
                        sum += ((*it).value * (*id).value);
                        ++it; ++id; --rA; --rD;
                    }
                }
                if (rA != 0) it += rA;
                if (rD != 0) id += rD;
                if (sum != 0)
                    c.terms.insert(cSize++, matrixTerm<T>(i, j, sum));
            }
        }
    }
}

#endif //DSACPP_SPAREMATRIX_H
