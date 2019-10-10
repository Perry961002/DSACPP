//
// Created by perry on 2019-10-11.
//

#ifndef DSACPP_CHAIN_H
#define DSACPP_CHAIN_H

#include <iostream>
#include <sstream>
#include "../MyExceptions.h"
#include "chainNode.h"
#include "linearList.h"

template <class T>
class test_chain : public linearList<T> {
public:
    //构造函数，复制构造函数和析构函数
    test_chain(int initialCapacity = 10);
    test_chain(const test_chain<T>&);
    ~test_chain();

    //ADT方法
    bool empty() const {return listSize == 0;}
    int size() const {return listSize;}
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(ostream& out) const;

    //重载[]运算符
    T& operator[](int theIndex){
        //如果元素不存在，则抛出异常
        checkIndex(theIndex);

        //移向索引为theIndex的结点
        chainNode<T>* currentNode = firstNode;
        for(int i = 0; i < theIndex; ++i)
            currentNode = currentNode->next;
        return currentNode->element;
    }

public:
    //迭代器类
    class iterator{
    public:
        typedef forward_iterator_tag iterator_category;  //向前迭代器

        //构造函数
        iterator(chainNode<T>* theNode = NULL) {node = theNode;}

        //解引用操作符
        T& operator*() const {return node->element;}
        T* operator->() const {return &node->element;}

        //迭代器加法操作
        iterator& operator++() {node = node->next; return *this;}  //前加
        iterator operator++(int){  //后加
            iterator old = *this;
            node = node->next;
            return old;
        }

        //相等检验
        bool operator!=(const iterator right) const {return node != right.node;}
        bool operator==(const iterator right) const {return node == right.node;}

    protected:
        chainNode<T>* node;  //结点指针
    };

    //首元素的迭代器
    iterator begin() {return iterator(firstNode);}
    //尾元素下一个位置的迭代器
    iterator end() {return iterator(NULL);}

protected:
    //如果索引无效，抛出异常
    void checkIndex(int theIndex) const;

    chainNode<T>* firstNode;  //指向链表第一个结点的指针
    int listSize;  //线性表的元素个数
};

//构造函数
template <class T>
test_chain<T>::test_chain(int initialCapacity) {
    if(initialCapacity < 1){
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << "Must be > 0";
        throw illegalParameterValue(s.str());
    }
    firstNode = NULL;
    listSize = 0;
}

//复制构造函数
template <class T>
test_chain<T>::test_chain(const test_chain<T> &theList) {
    listSize = theList.listSize;
    if(listSize == 0){
        //链表为空
        firstNode = NULL;
        return;
    }

    //链表非空
    chainNode<T>* sourceNode = theList.firstNode;  //要复制链表theIndex的结点
    firstNode = new chainNode<T>(sourceNode->element);  //复制链表theIndex的首元素
    sourceNode = sourceNode->next;
    chainNode<T>* targetNode = firstNode;  //当前链表*this的最后一个结点

    while(sourceNode != NULL){
        targetNode->next = new chainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next = NULL;  //链表结束
}

//析构函数
template <class T>
test_chain<T>::~test_chain() {
    //删除所有结点
    while(firstNode != NULL){
        //删除首结点
        chainNode<T>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

//检查索引是否有效
template <class T>
void test_chain<T>::checkIndex(int theIndex) const {
    //确定索引theIndex在0 和 listSize - 1之间
    if(theIndex < 0 || theIndex >= listSize){
        ostringstream s;
        s << "index = " << theIndex << "size = " << listSize;
        throw illegalParameterValue(s.str());
    }
}

//返回索引是theIndex的元素
template <class T>
T& test_chain<T>::get(int theIndex) const {
    //如果元素不存在，则抛出异常
    checkIndex(theIndex);

    //移向索引为theIndex的结点
    chainNode<T>* currentNode = firstNode;
    for(int i = 0; i < theIndex; ++i)
        currentNode = currentNode->next;
    return currentNode->element;
}

//返回元素theElement首次出现时的索引
template <class T>
int test_chain<T>::indexOf(const T &theElement) const {
    //搜索链表寻找元素theElement
    chainNode<T>* currentNode = firstNode;
    int theIndex = 0;  //当前结点的索引
    while(currentNode != NULL && currentNode->element != theElement){
        //移向下一个结点
        currentNode = currentNode->next;
        ++theIndex;
    }

    //确定是否找到所需的元素
    if(currentNode == NULL)
        return -1;
    else
        return theIndex;
}

//删除索引为theIndex的元素
template <class T>
void test_chain<T>::erase(int theIndex) {
    //如果元素不存在，则抛出异常
    checkIndex(theIndex);

    //索引有效，找到要删除的元素结点
    chainNode<T>* deleteNode;
    if(theIndex == 0){
        //删除链表的首结点
        deleteNode = firstNode;
        firstNode = firstNode->next;
    } else{
        //用p指向要删除结点的前驱结点
        chainNode<T>* p = firstNode;
        for(int i = 0; i < theIndex - 1; ++i)
            p = p->next;
        deleteNode = p->next;
        p->next = p->next->next;  //删除deleteNode指向的结点
    }
    --listSize;
    delete deleteNode;
}

//在索引为theIndex的位置上插入新元素theElement
template <class T>
void test_chain<T>::insert(int theIndex, const T &theElement) {
    //先检查索引是否有效
    if(theIndex < 0 || theIndex > listSize){
        //无效索引
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

    if(theIndex == 0)
        //在链表头插入
        firstNode = new chainNode<T>(theElement, firstNode);
    else{
        //寻找新元素的前驱
        chainNode<T>* p = firstNode;
        for(int i = 0; i < theIndex - 1; ++i)
            p = p->next;

        //在p之后插入
        p->next = new chainNode<T>(theElement, p->next);
    }
    ++listSize;
}

//把元素插入到一个输出流
template <class T>
void test_chain<T>::output(ostream &out) const {
    for(chainNode<T>* currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
        out << currentNode->element << " ";
}

//重载<<
template <class T>
ostream& operator<<(ostream& out, const test_chain<T>& x){
    x.output(out);
    return out;
}

#endif //DSACPP_CHAIN_H
