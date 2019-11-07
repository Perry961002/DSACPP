//
// Created by perry on 2019/11/7.
//

#ifndef DSACPP_LINKEDQUEUE_H
#define DSACPP_LINKEDQUEUE_H

#include "queue.h"
#include "../Chap6_LinkedList/chainNode.h"
#include "../MyExceptions.h"

//链表描述的队列
template <class T>
class linkedQueue : public Queue<T> {
public:
    //构造和析构函数
    linkedQueue(int initCapacity = 10) {queueFront = NULL; queueSize = 0;}
    ~linkedQueue();

    //判断是否为空
    bool empty() const { return queueSize == 0;}

    //返回元素个数
    int size() const { return queueSize;}

    //返回首元素的引用
    T& front() {
        if (queueSize == 0)
            throw queueEmpty();
        return queueFront->element;
    }

    //返回尾元素的引用
    T& back() {
        if (queueSize == 0)
            throw queueEmpty();
        return queueBack->element;
    }

    //插入和删除元素
    void push(const T& theElement);
    void pop();
private:
    chainNode<T> *queueFront, *queueBack;  //队列的首尾结点
    int queueSize;  //元素个数
};

//析构函数
template <class T>
linkedQueue<T>::~linkedQueue() {
    while (queueFront != NULL) {
        chainNode<T> *nextNode = queueFront->next;
        delete queueFront;
        queueFront = nextNode;
    }
}

//在队尾插入元素
template <class T>
void linkedQueue<T>::push(const T &theElement) {
    //申请新元素结点
    chainNode<T> *newNode = new chainNode<T>(theElement, NULL);

    //把新结点插入队尾
    if (queueSize == 0)
        queueFront = newNode;
    else
        queueBack->next = newNode;
    queueBack = newNode;

    ++queueSize;
}

//删除元素
template <class T>
void linkedQueue<T>::pop() {
    if (queueFront == NULL)
        throw queueEmpty();

    chainNode<T> *nextNode = queueFront->next;
    delete queueFront;
    queueFront = nextNode;
    --queueSize;
}

#endif //DSACPP_LINKEDQUEUE_H
