//
// Created by perry on 2019-09-04.
//

#ifndef DSACPP_LINEARLIST_H
#define DSACPP_LINEARLIST_H

#include <iostream>
using namespace std;

//一个线性表的抽象类
template <class T>
class linearList{
public:
    virtual ~linearList() {};

    //返回true，当线性表为空
    virtual bool empty() const = 0;

    //返回线性表的元素个数
    virtual int size() const = 0;

    //返回索引为theIndex的元素
    virtual T& get(int theIndex) const = 0;

    //返回元素theElement第一次出现时的索引
    virtual int indexOf(const T& theElement) const = 0;

    //删除索引为theindex的元素
    virtual void erase(int theIndex) = 0;

    //把theElement插入线性表中索引为theIndex的位置上
    virtual void insert(int theIndex, const T& theElement) = 0;

    //把线性表插入输出流out
    virtual void output(ostream& out) const = 0;
};

#endif //DSACPP_LINEARLIST_H
