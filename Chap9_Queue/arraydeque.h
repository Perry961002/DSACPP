//
// Created by perry on 2019/11/7.
//

#ifndef DSACPP_ARRAYDEQUE_H
#define DSACPP_ARRAYDEQUE_H

#include "deque.h"
#include "../MyExceptions.h"

//用数组描述的双端队列，使用循环队列
template <class T>
class arrayDeque : public Deque<T> {
private:
    int dequeFront;  //首元素的下标
    int dequeEnd;  //尾元素的下一个位置
    int arrayLength;  //数组容量
    T* deque;  //数组
};


#endif //DSACPP_ARRAYDEQUE_H
