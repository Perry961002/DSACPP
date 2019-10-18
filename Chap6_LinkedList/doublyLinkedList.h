//
// Created by perry on 2019/10/18.
//

#ifndef DSACPP_DOUBLYLINKEDLIST_H
#define DSACPP_DOUBLYLINKEDLIST_H

#include <sstream>
#include "extendedLinearList.h"
#include "../MyExceptions.h"

//带有双指针的结构体
template <class T>
struct chainNode{
    //数据成员
    T element;
    chainNode<T> *previous;  //前驱
    chainNode<T> *next;  //后继

    //构造方法
    chainNode() {}
    chainNode(const T& element) {this->element = element;}
    chainNode(const T& element, chainNode<T>* previous, chainNode<T>* next) {
        this->element = element;
        this->previous = previous;
        this->next = next;
    }
};

//双向链表类
template <class T>
class doublyLinkedList : public extendedLinearList<T>{
public:
    //构造和析构函数
    doublyLinkedList(int initialCapacity = 10);
    ~doublyLinkedList();

    //ADT函数
    bool empty() const {return listSize == 0;}
    int size() const { return  listSize;}
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(ostream& out) const;
    void clear();
    void push_back(const T& theElement);

    //设置大小为theSize
    void setSize(int theSize);

    //将索引为theIndex的元素值设置为theElement
    void set(int theIndex, const T& theElement);

    //首插入
    void push_front(const T& theElement);

    //首弹出
    void pop_front();
    //尾弹出
    void pop_back();

    //删除索引fromIndex至toIndex之间的元素
    void removeRange(int fromIndex, int toIndex);

    //反转链表
    void reverse();

    //交换两个链表
    void swap(doublyLinkedList<T>& theList);

    //获取首尾结点
    T& front() { return firstNode->element;}
    T& back() { return lastNode->element;}

    //判断*this是否和theList相等
    bool isEqual(const doublyLinkedList<T>& theList) const;

    //判断*this是否小于theList
    bool isLess(const doublyLinkedList<T>& theList) const;

    //重载[]运算符
    T& operator[](int theIndex) {
        //如果索引无效，则抛出异常
        checkIndex(theIndex);

        chainNode<T>* currendNode;
        //theIndex在前半部分
        if(theIndex < (listSize / 2)){
            currendNode = firstNode;
            for(int i = 0; i < theIndex; ++i)
                currendNode = currendNode->next;
        } else{
            currendNode = lastNode;
            for(int i = listSize - 1; i > theIndex; --i)
                currendNode = currendNode->previous;
        }
        return currendNode->element;
    }

public:
    //迭代器
    class iterator{
    public:
        typedef bidirectional_iterator_tag iterator_category;  //双向迭代器
        typedef T value_type;  //迭代器指向的数据类型
        typedef T* pointer;  //指针
        typedef T& reference;  //引用

        //构造函数
        iterator(chainNode<T>* theNode = NULL) {node = theNode;}

        //解引用操作符
        T& operator*() const { return node->element;}
        T* operator->() const { return  &node->element;}

        //迭代器加法操作
        iterator& operator++() {node = node->next; return *this;}  //前加
        iterator operator++(int){  //后加
            iterator old = *this;
            node = node->next;
            return old;
        }

        //迭代器减法操作
        iterator& operator--() {node = node->previous; return *this;}  //前加
        iterator operator--(int){  //后加
            iterator old = *this;
            node = node->previous;
            return old;
        }

        //相等检验
        bool operator!=(const iterator right) const { return node != right.node;}
        bool operator==(const iterator right) const { return node == right.node;}

    protected:
        chainNode<T>* node;  //结点指针
    };

    //首迭代器
    iterator begin() { return iterator(firstNode);}

    //尾后迭代器
    iterator end() { return iterator(NULL);}

protected:
    void checkIndex(int theIndex) const;
    chainNode<T>* firstNode;  //首结点
    chainNode<T>* lastNode;  //尾结点
    int listSize;  //长度
};

//构造函数
template <class T>
doublyLinkedList<T>::doublyLinkedList(int initialCapacity) {
    if(initialCapacity < 1){
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << "Must be > 0";
        throw illegalParameterValue(s.str());
    }
    firstNode = lastNode = NULL;
    listSize = 0;
}

//析构函数
template <class T>
doublyLinkedList<T>::~doublyLinkedList() {
    //从两个方向开始删除
    while(firstNode != lastNode){
        chainNode<T> *deleteFirst = firstNode, *deleteLast = lastNode;
        firstNode = firstNode->next;
        lastNode = lastNode->previous;
        delete deleteFirst;
        delete deleteLast;
    }
    delete firstNode;
}

//检查索引是否有效
template <class T>
void doublyLinkedList<T>::checkIndex(int theIndex) const {
    //确定索引theIndex在0 和 listSize - 1之间
    if(theIndex < 0 || theIndex >= listSize){
        ostringstream s;
        s << "index = " << theIndex << "size = " << listSize;
        throw illegalParameterValue(s.str());
    }
}

//取得索引theIndex的元素值
template <class T>
T& doublyLinkedList<T>::get(int theIndex) const {
    //如果索引无效，则抛出异常
    checkIndex(theIndex);

    chainNode<T>* currendNode;
    //theIndex在前半部分
    if(theIndex < (listSize / 2)){
        currendNode = firstNode;
        for(int i = 0; i < theIndex; ++i)
            currendNode = currendNode->next;
    } else{
        currendNode = lastNode;
        for(int i = listSize - 1; i > theIndex; --i)
            currendNode = currendNode->previous;
    }
    return currendNode->element;
}

//获取元素theElement第一次出现的索引
template <class T>
int doublyLinkedList<T>::indexOf(const T &theElement) const {
    chainNode<T>* p = firstNode;
    for(int i = 0; i < listSize; ++i){
        if(p->element == theElement)
            return i;
        p = p->next;
    }
    return -1;
}

//将元素输出到输出流
template <class T>
void doublyLinkedList<T>::output(ostream &out) const {
    for(chainNode<T> *currentNode = firstNode; currentNode != lastNode; currentNode = currentNode->next)
        out << currentNode->element << " ";
}

//重载<<运算符
template <class T>
ostream& operator<<(ostream& out, const doublyLinkedList<T>& theList){
    theList.output(out);
    return out;
}

//清表
template <class T>
void doublyLinkedList<T>::clear() {
    //从两个方向开始删除
    while(firstNode != lastNode){
        chainNode<T> *deleteFirst = firstNode, *deleteLast = lastNode;
        firstNode = firstNode->next;
        lastNode = lastNode->previous;
        delete deleteFirst;
        delete deleteLast;
    }
    firstNode = lastNode = NULL;
    listSize = 0;
}

#endif //DSACPP_DOUBLYLINKEDLIST_H
