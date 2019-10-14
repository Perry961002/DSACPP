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
class chain : public linearList<T> {
public:
    //构造函数，复制构造函数和析构函数
    chain(int initialCapacity = 10);
    chain(const chain<T>&);
    ~chain();

    //ADT方法
    bool empty() const {return listSize == 0;}
    int size() const {return listSize;}
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(ostream& out) const;

    //习题里的函数
    //使线性表的大小等于theSize
    void setSize(int theSize);

    //将索引为theIndex的元素替换为theElement
    void set(int theIndex, const T& theElement);

    //删除指定范围内的元素
    void removeRange(int fromIndex, int toIndex);

    //返回元素theElement最后出现的索引
    int lastIndexOf(const T& theElement) const;

    //是否和线性表theChain相等
    bool isEqual(const chain<T>& theChain) const;

    //是否小于线性表theChain
    bool isLess(const chain<T>& theChain) const;

    //交换两个线性表
    void swap(chain<T>& theChain);

    //翻转xianxingb
    void reverse();

    //清表
    void clear();

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
        typedef T value_type;  //迭代器指向的数据类型
        typedef T* pointer;  //指针
        typedef T& reference;  //引用

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
chain<T>::chain(int initialCapacity) {
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
chain<T>::chain(const chain<T> &theList) {
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
chain<T>::~chain() {
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
void chain<T>::checkIndex(int theIndex) const {
    //确定索引theIndex在0 和 listSize - 1之间
    if(theIndex < 0 || theIndex >= listSize){
        ostringstream s;
        s << "index = " << theIndex << "size = " << listSize;
        throw illegalParameterValue(s.str());
    }
}

//返回索引是theIndex的元素
template <class T>
T& chain<T>::get(int theIndex) const {
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
int chain<T>::indexOf(const T &theElement) const {
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
void chain<T>::erase(int theIndex) {
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
void chain<T>::insert(int theIndex, const T &theElement) {
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
void chain<T>::output(ostream &out) const {
    for(chainNode<T>* currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
        out << currentNode->element << " ";
}

//重载<<
template <class T>
ostream& operator<<(ostream& out, const chain<T>& x){
    x.output(out);
    return out;
}

//使线性表的大小等于theSize
template <class T>
void chain<T>::setSize(int theSize) {
    //如果数组的初始大小小于等于指定的值，则增加NULL元素
    //如果数组的初始大小大于指定的值，则删除多余元素
    if(theSize < 0){
        ostringstream s;
        s << "Set size = " << theSize << "Must be >= 0";
        throw illegalParameterValue(s.str());
    }
    if(listSize > theSize){
        //找到索引为theSize的前驱
        chainNode<T>* p = firstNode;
        for(int i = 0; i < theSize - 1; ++i)
            p = p->next;
        //删除所有结点
        while(p->next != NULL){
            chainNode<T>* currentNode = p->next;
            p->next = currentNode->next;
            delete currentNode;
        }
        listSize = theSize;
    }
}

//将索引为theIndex的元素替换为theElement
template <class T>
void chain<T>::set(int theIndex, const T &theElement) {
    //索引theIndex超出异常，则抛出异常
    checkIndex(theIndex);

    //寻找需要被替换的元素
    chainNode<T>* currentNode = firstNode;
    for(int i = 0; i < theIndex; ++i)
        currentNode = currentNode->next;
    currentNode->element = theElement;
}

//删除指定范围的元素
template <class T>
void chain<T>::removeRange(int fromIndex, int toIndex) {
    //确定索引是否有效
    if(fromIndex < 0 || toIndex >= listSize){
        //无效的索引
        ostringstream s;
        s << "Index  from" << fromIndex << " to " << toIndex << " size = " << listSize;
        throw illegalParameterValue(s.str());
    }

    //找到开始删除结点的前驱结点
    chainNode<T>* p = firstNode;
    for(int i = 0; i < fromIndex - 1; ++i)
        p = p->next;
    int needDeleteNum = (toIndex - fromIndex + 1);
    while(needDeleteNum > 0){
        chainNode<T>* currentNode = p->next;
        p->next = currentNode->next;
        delete currentNode;
        --needDeleteNum;
    }
    listSize -= (toIndex - fromIndex + 1);
}

//找到元素最后出现的位置
template <class T>
int chain<T>::lastIndexOf(const T &theElement) const{
    int theLastIndex = -1;
    chainNode<T>* currentNode = firstNode;
    for(int i = 0; i < listSize; ++i){
        if(currentNode->element == theElement)
            theLastIndex = i;
        currentNode = currentNode->next;
    }
    return theLastIndex;
}

//判断是否和线性表theChain相等
template <class T>
bool chain<T>::isEqual(const chain<T> &theChain) const {
    //同一个线性表
    if(this == &theChain)
        return true;

    //两个线性表的长度不等，肯定不相等
    if(listSize != theChain.listSize)
        return false;

    //比较每一个元素
    chainNode<T> *p = firstNode, *q = theChain.firstNode;
    while(p != NULL && q != NULL){
        //遇到不一样的元素就返回false
        if(p->element != q->element)
            return false;
        p = p->next;
        q = q->next;
    }

    return true;
}

//重载==运算符
template <class T>
bool operator==(const chain<T>& theLeftChain, const chain<T>& theRightChain){
    return theLeftChain.isEqual(theRightChain);
}

//重载!=运算符
template <class T>
bool operator!=(const chain<T>& theLeftChain, const chain<T>& theRightChain){
    return !theLeftChain.isEqual(theRightChain);
}

//判断是否小于线性表theChain
template <class T>
bool chain<T>::isLess(const chain<T> &theChain) const {
    //是同一个线性表
    if(this == &theChain)
        return false;

    //比较每一个元素
    chainNode<T> *p = firstNode, *q = theChain.firstNode;
    while(p != NULL && q != NULL){
        //当前线性表的元素更小
        if(firstNode->element < q->element)
            return true;
        else if(firstNode->element > q->element)
            //当前线性表的元素更大
            return false;
        p = p->next;
        q = q->next;
    }

    //当前线性表的长度更小
    if(p == NULL && q != NULL)
        return true;
    else
        return false;
}

//重载<运算符
template <class T>
bool operator<(const chain<T>& theLeftChain, const chain<T>& theRightChain){
    return theLeftChain.isLess(theRightChain);
}

//交换两个线性表
template <class T>
void chain<T>::swap(chain<T> &theChain) {
    //交换两个指针
    chainNode<T>* copyChain = theChain.firstNode;
    theChain.firstNode = firstNode;
    firstNode = copyChain;

    //交换线性表的长度
    int copyListsize = theChain.listSize;
    theChain.listSize = listSize;
    listSize = copyListsize;
}

//翻转链表
template <class T>
void chain<T>::reverse() {
    //最多只有一个结点的情况下不变
    if(listSize < 2) return;

    chainNode<T>* currentNode = firstNode->next;
    firstNode->next = NULL;
    //迭代
    while(currentNode != NULL){
        chainNode<T>* nextNode = currentNode->next;
        currentNode->next = firstNode;
        firstNode = currentNode;
        currentNode = nextNode;
    }
}

//清表
template <class T>
void chain<T>::clear() {
    //删除所有结点
    while(firstNode != NULL){
        //删除首结点
        chainNode<T>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
    listSize = 0;
}


#endif //DSACPP_CHAIN_H
