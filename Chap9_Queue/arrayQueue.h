//
// Created by perry on 2019/11/6.
//

#ifndef DSACPP_ARRAYQUEUE_H
#define DSACPP_ARRAYQUEUE_H

#include <sstream>
#include <algorithm>
#include "queue.h"
#include "../MyExceptions.h"

//数组描述的队列，环形队列
template <class T>
class arrayQueue : public Queue<T> {
public:
    //构造和析构函数
    arrayQueue(int initCapacity = 10);
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

    //删除队首元素
    void pop() {
        if (queueFront == queueBack)
            throw queueEmpty();
        queueFront = (queueFront + 1) % arrayLength;
        queue[queueFront].~T();
    };

    //在队尾插入元素
    void push(const T& theElement);
private:
    int queueFront;  //队首元素前一个位置的下标
    int queueBack;  //队尾元素的下标
    int arrayLength;  //队列的容量
    T* queue;  //元素数组
};

//构造函数
template <class T>
arrayQueue<T>::arrayQueue(int initCapacity) {
    if (initCapacity < 1) {
        ostringstream s;
        s << "Initial capacity = " << initCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initCapacity;
    queue = new T[arrayLength];
    queueFront = queueBack = 0;
}

//插入元素
template <class T>
void arrayQueue<T>::push(const T &theElement) {
    //队满，数组容量加倍
    if ((queueBack + 1) % arrayLength == queueFront) {
        //分配新的数组空间
        T* newQueue = new T[2 * arrayLength];

        //将原数组元素复制到新数组
        int start = (queueFront + 1) % arrayLength;
        if (start < 2)
            //元素环不包含0位置
            copy(queue + start, queue + start + arrayLength - 1, newQueue);
        else {
            //分成前后两部分复制
            copy(queue + start, queue + arrayLength, newQueue);
            copy(queue, queue + queueBack + 1, newQueue + arrayLength - start);
        }

        //设置新数组的首和尾的元素位置
        queueFront = 2 *arrayLength - 1;
        queueBack = arrayLength - 2;
        arrayLength *= 2;
        delete [] queue;
        queue = newQueue;
    }

    //插入到队列尾部
    queueBack = (queueBack + 1) % arrayLength;
    queue[queueBack] = theElement;
}

#endif //DSACPP_ARRAYQUEUE_H
