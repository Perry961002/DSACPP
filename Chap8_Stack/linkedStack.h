//
// Created by perry on 2019/11/5.
//

#ifndef DSACPP_LINKEDSTACK_H
#define DSACPP_LINKEDSTACK_H

#include "stack.h"
#include "../Chap6_LinkedList/chainNode.h"
#include "../MyExceptions.h"

//链表描述的栈
template <class T>
class linkedStack : public Stack<T> {
public:
    //构造函数
    linkedStack(int initCapacity = 10) {stackTop = NULL; stackSize = 0;}

    //析构函数
    ~linkedStack();

    //判空
    bool empty() const { return stackSize == 0;}

    //返回栈的大小
    int size() const { return stackSize;}

    //返回栈顶的引用
    T& top() {
        if (stackSize == 0)
            throw stackEmpty();
        return stackTop->element;
    }

    //删除栈顶
    void pop();

    //元素theElement入栈
    void push(const T& theElement) {
        stackTop = new chainNode<T>(theElement, stackTop);
        ++stackSize;
    }
private:
    chainNode<T>* stackTop;  //栈顶指针
    int stackSize;  //元素个数
};

//析构函数
template <class T>
linkedStack<T>::~linkedStack() {
    while (stackTop != NULL) {
        chainNode<T>* nextNode = stackTop->next;
        delete stackTop;
        stackTop = nextNode;
    }
}

//删除栈顶元素
template <class T>
void linkedStack<T>::pop() {
    if (stackSize == 0)
        throw stackEmpty();

    chainNode<T>* nextNode = stackTop->next;
    delete stackTop;
    stackTop = nextNode;
    --stackSize;
}

#endif //DSACPP_LINKEDSTACK_H
