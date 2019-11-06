//
// Created by perry on 2019/11/6.
//

#ifndef DSACPP_ARRAYQUEUE_H
#define DSACPP_ARRAYQUEUE_H

#include "queue.h"
#include "../MyExceptions.h"

//数组描述的队列，环形队列
template <class T>
class arrayQueue : public Queue<T> {
public:
    //构造和析构函数
    arrayQueue(int initialCapacity = 10);
    ~arrayQueue() {delete [] queue;}

    //判断队列是否为空
    bool empty() const { return (queueFront == queueBack);}

    //队列元素的个数
    int size() const { return (queueBack - queueFront + arrayLength) % arrayLength;}

    //队首元素的引用
    T& front() {
        //队空，抛出异常
        if (queueFront == queueBack)
            throw queueEmpty();
        return queue[(queueFront + 1) % arrayLength];
    }

    //队尾元素的引用
    T& back() {
        //队空，抛出异常
        if (queueFront == queueBack)
            throw queueEmpty();
        return queue[queueBack];
    }
private:
    int queueFront;  //队首元素前一个位置的下标
    int queueBack;  //队尾元素的下标
    int arrayLength;  //队列的容量
    T* queue;  //元素数组
};

#endif //DSACPP_ARRAYQUEUE_H
