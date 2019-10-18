//
// Created by perry on 2019/10/17.
//

#ifndef DSACPP_CIRCULARLISTWITHHEADER__H
#define DSACPP_CIRCULARLISTWITHHEADER__H

#include <ostream>
#include <sstream>
#include "../MyExceptions.h"
#include "extendedLinearList.h"
#include "chainNode.h"

//带头结点的循环链表
template <class T>
class circularListWithHeader : public extendedLinearList<T> {
public:
    //构造函数和析构函数
    circularListWithHeader(int initialCapacity = 10);
    ~circularListWithHeader();

    //ADT函数
    bool empty() const {return listSize == 0;}
    int size() const { return  listSize;}
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(std::ostream& out) const;
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

    //删除索引fromIndex至toIndex之间的元素
    void removeRange(int fromIndex, int toIndex);

    //反转链表
    void reverse();

    //交换两个链表
    void swap(circularListWithHeader<T>& theList);

    //获取首尾结点
    T& front() {return headerNode->next == headerNode ? lastNode->element : headerNode->next->element;}
    T& back() { return lastNode->element;}

    //判断*this是否和theList相等
    bool isEqual(const circularListWithHeader<T>& theList) const;

    //判断*this是否小于theList
    bool isLess(const circularListWithHeader<T>& theList) const;

    //重载[]运算符
    T& operator[](int theIndex){
        //如果索引不存在，则抛出异常
        checkIndex(theIndex);

        if(theIndex == 0)
            return headerNode->next->element;
        else if(theIndex == listSize - 1)
            return lastNode->element;
        else{
            chainNode<T>* currentNode = headerNode->next;
            for(int i = 0; i < theIndex; ++i)
                currentNode = currentNode->next;
            return currentNode->element;
        }
    }

public:
    //前向迭代器
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
    iterator begin() {return headerNode->next == headerNode ? NULL : headerNode->next;}

    //尾元素的下一个位置
    iterator end() {return lastNode->next;}

protected:
    //检查索引是否有效
    void checkIndex(int theIndex) const;

    chainNode<T>* headerNode;  //头结点
    chainNode<T>* lastNode;  //指向尾结点的指针
    int listSize;  //长度
};

//构造函数
template <class T>
circularListWithHeader<T>::circularListWithHeader(int initialCapacity) {
    if(initialCapacity < 1){
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << "Must be > 0";
        throw illegalParameterValue(s.str());
    }
    headerNode = new chainNode<T>();
    headerNode->next = headerNode;
    listSize = 0;
}

//析构函数
template <class T>
circularListWithHeader<T>::~circularListWithHeader() {
    //删除头结点之后的结点
    while(headerNode->next != headerNode) {
        chainNode<T>* deleteNode = headerNode->next;
        headerNode->next = headerNode->next->next;
        delete deleteNode;
    }
}

//检查索引是否有效
template <class T>
void circularListWithHeader<T>::checkIndex(int theIndex) const {
    //确定索引theIndex在0 和 listSize - 1之间
    if(theIndex < 0 || theIndex >= listSize){
        std::ostringstream s;
        s << "index = " << theIndex << "size = " << listSize;
        throw illegalParameterValue(s.str());
    }
}

//取得索引theIndex上的元素
template <class T>
T& circularListWithHeader<T>::get(int theIndex) const {
    //如果索引不存在，则抛出异常
    checkIndex(theIndex);

    //遍历寻找
    chainNode<T>* currentNode = headerNode->next;
    for(int i = 0; i < theIndex; ++i)
        currentNode = currentNode->next;
    return currentNode->element;
}

//查找元素theElement的索引
template <class T>
int circularListWithHeader<T>::indexOf(const T &theElement) const {
    //将元素theElement放入头结点
    headerNode->element = theElement;

    //在链表中搜索元素theElement
    chainNode<T>* currentNode = headerNode->next;
    int index = 0;  //当前结点的索引
    while(currentNode->element != theElement){
        //移到下一个结点
        currentNode = currentNode->next;
        ++index;
    }

    //确定是否找到
    if(currentNode == headerNode)
        return -1;
    else
        return index;
}

//删除索引为theIndex的元素
template <class T>
void circularListWithHeader<T>::erase(int theIndex) {
    //如果索引不存在，则抛出异常
    checkIndex(theIndex);

    //找到需要删除的结点
    chainNode<T>* deleteNode;
    if(theIndex == 0){
        //删除首结点
        deleteNode = headerNode->next;
        if(headerNode->next == lastNode)
            //只含一个元素
            headerNode->next = headerNode;
        else
            //连接到第二个元素
            headerNode->next = headerNode->next->next;
    } else if(theIndex == listSize - 1){
        //删除多于一个结点的链表的尾结点
        deleteNode = lastNode;
        //找到倒数第二个结点
        chainNode<T>* p = headerNode;
        while(p->next != lastNode)
            p = p->next;
        lastNode = p;
        lastNode->next = headerNode;
    } else{
        //删除中间部分
        chainNode<T>* p = headerNode;
        for(int i = 0; i < theIndex; ++i)
            p = p->next;
        deleteNode = p->next;
        p->next = p->next->next;
    }
    delete deleteNode;
    --listSize;
}

//把元素theElement插入到索引为theIndex的位置
template <class T>
void circularListWithHeader<T>::insert(int theIndex, const T &theElement) {
    //先检查索引是否有效
    if(theIndex < 0 || theIndex > listSize){
        //无效索引
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }
    //在首部插入
    if(theIndex == 0){
        if(headerNode->next == headerNode)
            //空表
            headerNode->next = lastNode = new chainNode<T>(theElement, headerNode);
        else
            //非空
            headerNode->next = new chainNode<T>(theElement, headerNode->next);
    } else if(theIndex == listSize){
        //非空且在尾部插入
        lastNode->next = new chainNode<T>(theElement, headerNode);
        lastNode = lastNode->next;
    } else{
        //在其他位置插入
        //找到需要插入位置的前驱
        chainNode<T>* p = headerNode;
        for(int i = 0; i < theIndex; ++i)
            p = p->next;
        p->next = new chainNode<T>(theElement, p->next);
    }
    ++listSize;
}

//将链表的元素插入到输出流
template <class T>
void circularListWithHeader<T>::output(std::ostream &out) const {
    for(chainNode<T>* currentNode = headerNode->next; currentNode != headerNode; currentNode = currentNode->next)
        out << currentNode->element << " ";
}

//重载<<运算符
template <class T>
ostream& operator<<(ostream& out, circularListWithHeader<T>& x){
    x.output(out);
    return out;
}

//清表
template <class T>
void circularListWithHeader<T>::clear() {
    //删除头结点之后的结点
    while(headerNode->next != headerNode) {
        chainNode<T>* deleteNode = headerNode->next;
        headerNode->next = headerNode->next->next;
        delete deleteNode;
    }
    lastNode = NULL;
    listSize = 0;
}

//设置大小为theSize
template <class T>
void circularListWithHeader<T>::setSize(int theSize) {
    //如果数组的初始大小小于等于指定的值，则不增加元素
    //如果数组的初始大小大于指定的值，则删除多余元素
    if(theSize < 0){
        ostringstream s;
        s << "Set size = " << theSize << "Must be >= 0";
        throw illegalParameterValue(s.str());
    }
    if(listSize > theSize){
        //找到索引是theSize-1的结点
        chainNode<T>* p = headerNode;
        for(int i = 0; i < theSize; ++i)
            p = p->next;
        //删除p之后的结点
        while(p->next != headerNode){
            chainNode<T>* deleteNode = p->next;
            p->next = p->next->next;
            delete deleteNode;
        }
        lastNode = p;
        listSize = theSize;
    }
}

//将索引为theIndex的元素的值设为theElement
template <class T>
void circularListWithHeader<T>::set(int theIndex, const T &theElement) {
    //如果索引超出范围，则抛出异常
    checkIndex(theIndex);

    chainNode<T>* currentNode = headerNode;
    for(int i = 0; i <= theIndex; ++i)
        currentNode = currentNode->next;
    currentNode->element = theElement;
}

//尾插入
template <class T>
void circularListWithHeader<T>::push_back(const T &theElement) {
    if(headerNode->next == headerNode)
        //空表
        headerNode->next = lastNode = new chainNode<T>(theElement, headerNode);
    else{
        //非空
        lastNode->next = new chainNode<T>(theElement, headerNode);
        lastNode = lastNode->next;
    }
    ++listSize;
}

//首插入
template <class T>
void circularListWithHeader<T>::push_front(const T &theElement) {
    if(headerNode->next == headerNode)
        //空表
        headerNode->next = lastNode = new chainNode<T>(theElement, headerNode);
    else
        //非空
        headerNode->next = new chainNode<T>(theElement, headerNode->next);
    ++listSize;
}

//首弹出
template <class T>
void circularListWithHeader<T>::pop_front() {
    //空表
    if(headerNode->next == headerNode)
        return;
    //不空
    chainNode<T>* deleteNode = headerNode->next;
    if(headerNode->next == lastNode)
        //只含一个元素
        headerNode->next = headerNode;
    else
        //连接到第二个元素
        headerNode->next = headerNode->next->next;
    delete deleteNode;
    --listSize;
}

//删除索引为fromIndex至toIndex之间的元素
template <class T>
void circularListWithHeader<T>::removeRange(int fromIndex, int toIndex) {
    //确定索引是否有效
    if(fromIndex < 0 || toIndex >= listSize){
        //无效的索引
        ostringstream s;
        s << "Index  from" << fromIndex << " to " << toIndex << " size = " << listSize;
        throw illegalParameterValue(s.str());
    }
    //找到需要删除的起始结点的前驱
    chainNode<T>* p = headerNode;
    for(int i = 0; i < fromIndex; ++i)
        p = p->next;
    //开始删除结点
    for(int i = fromIndex; i <= toIndex; ++i){
        chainNode<T>* deleteNode = p->next;
        p->next = p->next->next;
        delete deleteNode;
    }
    //如果末尾结点也在范围之内
    if(toIndex == listSize - 1)
        lastNode = p;
    listSize -= (toIndex - fromIndex + 1);
}

//反转链表
template <class T>
void circularListWithHeader<T>::reverse() {
    //只有最多一个元素的话不用反转
    if(listSize < 2) return;

    //先断开循环，再反转
    lastNode->next = NULL;
    chainNode<T>* p = headerNode->next->next;
    lastNode = headerNode->next;
    headerNode->next = lastNode;
    while(p != NULL){
        chainNode<T>* currentNode = p;
        p = p->next;
        currentNode->next = headerNode->next;
        headerNode->next = currentNode;
    }
    lastNode->next = headerNode;
}

//交换两个链表
template <class T>
void circularListWithHeader<T>::swap(circularListWithHeader<T> &theList) {
    //交换两个头指针
    chainNode<T>* copyChain = theList.headerNode;
    theList.headerNode = headerNode;
    headerNode = copyChain;
    //交换两个lastnode结点
    copyChain = theList.lastNode;
    theList.lastNode = lastNode;
    lastNode = copyChain;
    //交换线性表的长度
    int copyListsize = theList.listSize;
    theList.listSize = listSize;
    listSize = copyListsize;
}

//判断*this是否和theList相等
template <class T>
bool circularListWithHeader<T>::isEqual(const circularListWithHeader<T> &theList) const {
    //同一个链表
    if(this == &theList)
        return true;
    //长度不等的话链表肯定不等
    if(listSize != theList.listSize)
        return false;
    //比较每一个元素
    chainNode<T> *p = headerNode->next, *q = theList.headerNode->next;
    while(p != headerNode){
        if(p->element != q->element)
            return false;
        p = p->next;
        q = q->next;
    }
    return true;
}

//重载==运算符
template <class T>
bool operator==(const circularListWithHeader<T> &theLeftList, const circularListWithHeader<T> &theRightList){
    return theLeftList.isEqual(theRightList);
}

//判断*this是否小于theList
template <class T>
bool circularListWithHeader<T>::isLess(const circularListWithHeader<T> &theList) const {
    //同一个链表
    if(this == &theList)
        return false;

    //比较每一个元素
    chainNode<T> *p = headerNode->next, *q = theList.headerNode->next;
    while(p != headerNode && q != theList.headerNode){
        //*this当前元素更小
        if(p->element < q->element)
            return true;
        //*this当前元素更小
        else if(p->element > q->element)
            return false;
        p = p->next;
        q = q->next;
    }
    //*this的长度更小
    if(p == headerNode && p != theList.headerNode)
        return true;
    else
        return false;
}

//重载<运算符
template <class T>
bool operator<(const circularListWithHeader<T> &theLeftList, const circularListWithHeader<T> &theRightList){
    return theLeftList.isLess(theRightList);
}

#endif //DSACPP_CIRCULARLISTWITHHEADER__H
