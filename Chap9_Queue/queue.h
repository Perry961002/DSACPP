//
// Created by perry on 2019/11/6.
//

#ifndef DSACPP_QUEUE_H
#define DSACPP_QUEUE_H

//队列的抽象类
template <class T>
class Queue {
public:
    virtual ~Queue() {}

    //队列为空，返回true
    virtual bool empty() const = 0;

    //返回队列里的元素个数
    virtual int size() const = 0;

    //返回队头元素的引用
    virtual T& front() = 0;

    //返回尾元素的引用
    virtual T& back() = 0;

    //删除首元素
    virtual void pop() = 0;

    //把元素theElement插入队尾
    virtual void push(const T& theElement) = 0;
};

#endif //DSACPP_QUEUE_H
