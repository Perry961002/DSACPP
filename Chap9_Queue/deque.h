//
// Created by perry on 2019/11/7.
//

#ifndef DSACPP_DEQUE_H
#define DSACPP_DEQUE_H

//双端队列的抽象类
template <class T>
class Deque {
    //虚析构
    virtual ~Deque() {}

    //判断双端队列是否为空
    virtual bool empty() const = 0;

    //返回双端队列中元素个数
    virtual int size() const = 0;

    //双端队列首元素的引用
    virtual T& front() = 0;

    //双端队列尾元素的引用
    virtual T& back() = 0;

    //在双端队列的头部插入
    virtual void push_front(const T& theElement) = 0;

    //在双端队列的头部删除元素
    virtual void pop_front() = 0;

    //在双端队列的尾部插入
    virtual void push_back(const T& theElement) = 0;

    //在双端队列的尾部删除元素
    virtual void pop_back() = 0;

    //清空队列
    virtual void clear() = 0;
};


#endif //DSACPP_DEQUE_H
