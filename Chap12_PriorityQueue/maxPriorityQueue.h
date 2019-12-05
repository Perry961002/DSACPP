//
// Created by perry on 2019/12/4.
//

#ifndef DSACPP_MAXPRIORITYQUEUE_H
#define DSACPP_MAXPRIORITYQUEUE_H

//大根堆的抽象类
template <class T>
class maxPriorityQueue {
public:
    virtual ~maxPriorityQueue() {}
    //判断是否为空
    virtual bool empty() const = 0;

    //返回队列的元素个数
    virtual int size() const = 0;

    //返回优先级最大的元素的引用
    virtual const T& top() = 0;

    //删除队首元素
    virtual void pop() = 0;

    //插入元素theElement
    virtual void push(const T& theElement) = 0;
};

#endif //DSACPP_MAXPRIORITYQUEUE_H
