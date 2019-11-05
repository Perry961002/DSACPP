//
// Created by perry on 2019/11/5.
//

#ifndef DSACPP_ARRAYSTACK_H
#define DSACPP_ARRAYSTACK_H

#include <sstream>
#include "stack.h"
#include "../MyExceptions.h"
#include "../Chap5_ArrayList/changeLength1D.h"

//数组描述的栈
template <class T>
class arrayStack : public Stack<T> {
public:
    //构造和析构函数
    arrayStack(int initCapacity = 10);
    ~arrayStack() {delete [] stack;}

    //判断
    bool empty() const {return stackTop == -1;}

    //取得栈的大小
    int size() const {return stackTop + 1;}

    //取得栈顶的引用
    T& top() {
        if (stackTop == -1)
            throw stackEmpty();
        return stack[stackTop];
    }

    //删除栈顶元素
    void pop() {
        if (stackTop == -1)
            throw stackEmpty();
        stack[stackTop--].~T();
    }

    //将元素theElement压入栈
    void push(const T& theElement);
private:
    int stackTop;  //当前栈顶
    int arrayLength;  //栈的容量
    T *stack;  //元素数组
};

//构造函数
template <class T>
arrayStack<T>::arrayStack(int initCapacity) {
    if (initCapacity < 1) {
        ostringstream s;
        s << "Initial capacity = " << initCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initCapacity;
    stack = new T[arrayLength];
    stackTop = -1;
}

//将元素theElement压入栈
template <class T>
void arrayStack<T>::push(const T &theElement) {
    //如果空间已满，容量加倍
    if (stackTop == (arrayLength - 1)) {
        changeLength1D(stack, arrayLength, arrayLength * 2);
        arrayLength *= 2;
    }
    //栈顶插入
    stack[++stackTop] = theElement;
}

#endif //DSACPP_ARRAYSTACK_H
