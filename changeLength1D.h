//
// Created by perry on 2019-09-04.
//

#ifndef DSACPP_CHANGELENGTH1D_H
#define DSACPP_CHANGELENGTH1D_H

#include "MyExceptions.h"

template <class T>
void changeLength1D(T& a, int oldLength, int newLength){
    if(newLength < 0)
        throw illegalParameterValue("new length must be >= 0");
    T* temp = new T[newLength];  // 新数组
    int number = min(oldLength, newLength);  // 需要复制的元素个数
    copy(a, a + number, temp);
    delete [] a;  // 释放老数组的内存空间
    a = temp;
}

#endif //DSACPP_CHANGELENGTH1D_H
