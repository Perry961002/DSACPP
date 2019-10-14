//
// Created by perry on 2019/10/14.
//

#ifndef DSACPP_EXTENDEDLINEARLIST_H
#define DSACPP_EXTENDEDLINEARLIST_H

#include "linearList.h"

//扩展的线性表的抽象类
template <class T>
class extendedLinearList : public linearList<T>{
public:
    //虚析构函数
    virtual ~extendedLinearList() {}

    //清表
    virtual void clear() = 0;

    //将元素theElement插入到表尾
    virtual void push_back(const T& theElement) = 0;
};

#endif //DSACPP_EXTENDEDLINEARLIST_H
