//
// Created by perry on 2019/11/5.
//

#ifndef DSACPP_STACK_H
#define DSACPP_STACK_H

//抽象类栈
template <class T>
class Stack {
public:
    virtual ~Stack() {}
    //判断栈是否为空
    virtual bool empty() const = 0;

    //返回栈中元素的个数
    virtual int size() const = 0;

    //返回栈顶元素的引用
    virtual T& top() = 0;

    //删除栈顶元素
    virtual void pop() = 0;

    //将元素theElement压入栈顶
    virtual void push(const T& theElement) = 0;
};

#endif //DSACPP_STACK_H
