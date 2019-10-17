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
    circularListWithHeader();
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

    //获取首尾结点
    T& front() {return headerNode->next == headerNode ? lastNode->element : headerNode->next->element;}
    T& back() { return lastNode->element;}

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
circularListWithHeader<T>::circularListWithHeader() {
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
    //释放头结点
    delete headerNode;
    //尾结点
    delete lastNode;
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
        headerNode->next = headerNode->next->next;
        if(listSize == 0)
            lastNode = NULL;
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
        headerNode->next = new chainNode<T>(theElement, headerNode->next);
        //空表
        if(listSize == 0)
            lastNode = headerNode->next;
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
    for(chainNode<T>* currentNode = headerNode->next; currentNode->next != headerNode; currentNode = currentNode->next)
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
    //尾结点
    delete lastNode;
    listSize = 0;
}

//尾插入
template <class T>
void circularListWithHeader<T>::push_back(const T &theElement) {
    chainNode<T>* newNode = new chainNode<T>(theElement, headerNode);
    if(headerNode->next == headerNode)
        //空表
        headerNode->next = lastNode = newNode;
    else{
        lastNode->next = newNode;
        lastNode = lastNode->next;
    }
    ++listSize;
}

#endif //DSACPP_CIRCULARLISTWITHHEADER__H
