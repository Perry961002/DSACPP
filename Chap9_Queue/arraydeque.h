//
// Created by perry on 2019/11/7.
//

#ifndef DSACPP_ARRAYDEQUE_H
#define DSACPP_ARRAYDEQUE_H

#include <sstream>
#include <algorithm>
#include "deque.h"
#include "../MyExceptions.h"

//用数组描述的双端队列，使用循环队列
template <class T>
class arrayDeque : public Deque<T> {
public:
    //构造函数和析构函数
    arrayDeque(int initCapacity = 10);
    ~arrayDeque() {delete [] deque;}

    //判空
    bool empty() const { return dequeFront == dequeEnd;}

    //返回元素个数
    int size() const { return (dequeEnd - dequeFront + arrayLength) % arrayLength;}

    //首元素的引用
    T& front() {
        if (dequeFront == dequeEnd)
            throw dequeEmpty();
        return deque[dequeFront];
    }

    //尾元素的引用
    T& back() {
        if (dequeFront == dequeEnd)
            throw dequeEmpty();
        return deque[(dequeEnd - 1 + arrayLength) % arrayLength];
    }

    //在头部插入和删除
    void push_front(const T& theElement);
    void pop_front();

    //在尾部插入和删除
    void push_back(const T& theElement);
    void pop_back();

    //清空
    void clear() {
        delete [] deque;
        dequeFront = dequeEnd = 0;
    }

    //随机访问迭代器
    class iterator {
    public:
        typedef random_access_iterator_tag iterator_category;  // 随机访问迭代器
        typedef T value_type;  //迭代器指向的数据类型
        typedef ptrdiff_t difference_type; // 标准库里一种与机器相关的数据类型，常用来表示两个指针相减的结果
        typedef T* pointer;  //指针
        typedef T& reference;  //引用

        //迭代器的构造函数
        iterator(T* thePosition = 0, int theIndex = 0, int theSize = 0) {
            position = thePosition;
            index = theIndex;
            size = theSize;
        }

        // 解引用操作符
        T& operator*() const {return *(position + index);}
        T* operator->() const {return &*(position + index);}

        // 迭代器的值增加
        iterator& operator++() {index = (index + 1) % size; return *this;}  // 前置
        iterator operator++(int){ // 后置
            iterator old = *this;
            index = (index + 1) % size;
            return old;
        }
        iterator operator+(int n){
            // +运算符, 实现随机访问
            iterator old = *this;
            old.index = (old.index + n) % size;
            return old;
        }
        iterator& operator+=(int n){index = (index + n) % size; return *this;}

        // 迭代器减少
        iterator& operator--() {index = (index - 1 + size) % size; return *this;}  // 前置
        iterator operator--(int){ // 后置
            iterator old = *this;
            index = (index - 1 + size) % size;;
            return old;
        }
        iterator operator-(int n){
            // -运算符，实现随机访问
            iterator old = *this;
            old.position = (old.index - n + size) % size;
            return old;
        }
        iterator& operator-=(int n) {index = (index - n + size) % size; return *this;}

        //测试是否相等
        bool operator!=(const iterator right) const {return (position + index) != (right.position + right.index);}
        bool operator==(const iterator right) const {return (position + index) == (right.position + right.index);}
    private:
        T *position;  //指针
        int index, size;  //相对位置，容量
    };

    //返回首元素迭代器和尾元素下一个位置的迭代器
    iterator begin() { return iterator(deque, dequeFront, arrayLength);}
    iterator end() { return iterator(deque, dequeEnd, arrayLength);}

private:
    void extend();  //数组装满时扩容，容量加倍
    int dequeFront;  //首元素的下标
    int dequeEnd;  //尾元素的下一个位置
    int arrayLength;  //数组容量
    T* deque;  //数组
};

//构造函数
template <class T>
arrayDeque<T>::arrayDeque(int initCapacity) {
    if (initCapacity < 1) {
        ostringstream s;
        s << "Initial capacity = " << initCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initCapacity;
    deque = new T[arrayLength];
    dequeFront = dequeEnd = 0;
}

//数组容量用完时进行扩展
template <class T>
void arrayDeque<T>::extend() {
    //分配新的数组空间
    T* newDeque = new T[2 * arrayLength];

    //把原数组的元素复制到新的数组中
    if (dequeFront < 2)
        //元素环不会被0位置截断
        copy(deque + dequeFront, deque + dequeFront + arrayLength - 1, newDeque);
    else {
        //元素环被0位置截断
        copy(deque + dequeFront, deque + arrayLength, newDeque);  //复制前半部分
        copy(deque, deque + dequeEnd, newDeque + arrayLength - dequeFront);  //复制后半部分
    }

    //设置新数组的首尾位置
    dequeFront = 0;
    dequeEnd = arrayLength - 1;
    arrayLength *= 2;
    delete [] deque;
    deque = newDeque;
}

//头部插入元素
template <class T>
void arrayDeque<T>::push_front(const T &theElement) {
    //队列已满，扩容
    if ((dequeFront - 1 + arrayLength) % arrayLength == dequeEnd)
        extend();

    //dequeFront前移，插入元素
    dequeFront = (dequeFront - 1 + arrayLength) % arrayLength;
    deque[dequeFront] = theElement;
}

//头部删除元素
template <class T>
void arrayDeque<T>::pop_front() {
    if (dequeFront == dequeEnd)
        throw dequeEmpty();
    deque[dequeFront % arrayLength].~T();
    dequeFront = (dequeFront + 1) % arrayLength;
}

//尾部插入元素
template <class T>
void arrayDeque<T>::push_back(const T &theElement) {
    //队列已满，扩容
    if ((dequeEnd + 1) % arrayLength == dequeFront)
        extend();

    //插入元素，dequeEnd后移
    deque[dequeEnd] = theElement;
    dequeEnd = (dequeEnd + 1) % arrayLength;
}

//尾部删除元素
template <class T>
void arrayDeque<T>::pop_back() {
    if (dequeFront == dequeEnd)
        throw dequeEmpty();
    dequeEnd = (dequeEnd - 1 +arrayLength) % arrayLength;
    deque[dequeEnd].~T();
}


#endif //DSACPP_ARRAYDEQUE_H
