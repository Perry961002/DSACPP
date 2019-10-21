//
// Created by perry on 2019/10/20.
//

#ifndef DSACPP_DOUBLYLINKEDLISTWITHHEADER_H
#define DSACPP_DOUBLYLINKEDLISTWITHHEADER_H

#include <sstream>
#include <algorithm>
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

//带头结点的双向循环链表类
template <class T>
class doublyLinkedListWithHeader : public extendedLinearList<T> {
public:
    //构造和析构函数
    doublyLinkedListWithHeader(int initialCapacity = 10);
    ~doublyLinkedListWithHeader();
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

    //将索引为theIndex的元素值设置为theElement
    void set(int theIndex, const T& theElement);

    //首插入
    void push_front(const T& theElement);

    //首弹出
    void pop_front();
    //尾弹出
    void pop_back();

    //反转链表
    void reverse();

    //交换两个链表
    void swap(doublyLinkedListWithHeader<T>& theList);

    //删除索引fromIndex至toIndex之间的元素
    void removeRange(int fromIndex, int toIndex);

    //获取首尾结点
    T& front() { return headerNode->next->element;}
    T& back() { return headerNode->previous->element;}

    //判断*this是否和theList相等
    bool isEqual(const doublyLinkedListWithHeader<T>& theList) const;
    //判断*this是否小于theList
    bool isLess(const doublyLinkedListWithHeader<T>& theList) const;

public:
    //迭代器
    class iterator {
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
    iterator begin() { return iterator(headerNode->next);}

    //尾后迭代器
    iterator end() { return iterator(headerNode);}

protected:
    void checkIndex(int theIndex) const;
    chainNode<T>* headerNode;  //头结点
    int listSize;  //链表长度
};

//构造函数
template <class T>
doublyLinkedListWithHeader<T>::doublyLinkedListWithHeader(int initialCapacity) {
    if(initialCapacity < 1){
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << "Must be > 0";
        throw illegalParameterValue(s.str());
    }
    headerNode = new chainNode<T>();
    headerNode->next = headerNode;
    headerNode->previous = headerNode;
    listSize = 0;
}

//析构函数
template <class T>
doublyLinkedListWithHeader<T>::~doublyLinkedListWithHeader() {
    //删除所有元素
    while (headerNode->next != headerNode) {
         chainNode<T>* deleteNode = headerNode->next;
         headerNode->next = deleteNode->next;
         deleteNode->next->previous = headerNode;
         delete deleteNode;
    }
}

//检查索引是否有效
template <class T>
void doublyLinkedListWithHeader<T>::checkIndex(int theIndex) const {
    //确定索引theIndex在0 和 listSize - 1之间
    if(theIndex < 0 || theIndex >= listSize){
        ostringstream s;
        s << "index = " << theIndex << "size = " << listSize;
        throw illegalParameterValue(s.str());
    }
}

//取得索引theIndex上的元素
template <class T>
T& doublyLinkedListWithHeader<T>::get(int theIndex) const {
    //索引不存在，则抛出异常
    checkIndex(theIndex);

    //索引在前半部分
    chainNode<T>* currendNode = headerNode;
    if (theIndex < (listSize / 2)) {
        for(int i = 0; i <= theIndex; ++i)
            currendNode = currendNode->next;
    } else {
        //在后半部分
        for(int i = listSize; i > theIndex; --i)
            currendNode = currendNode->previous;
    }
    return currendNode->element;
}

//将索引theIndex上的元素值设为theElement
template <class T>
void doublyLinkedListWithHeader<T>::set(int theIndex, const T &theElement) {
    //索引不存在，则抛出异常
    checkIndex(theIndex);

    //索引在前半部分
    chainNode<T>* currendNode = headerNode;
    if (theIndex < (listSize / 2)) {
        for(int i = 0; i <= theIndex; ++i)
            currendNode = currendNode->next;
    } else {
        //在后半部分
        for(int i = listSize; i > theIndex; --i)
            currendNode = currendNode->previous;
    }
    currendNode->element = theElement;
}

//元素theElement第一次出现时的索引
template <class T>
int doublyLinkedListWithHeader<T>::indexOf(const T &theElement) const {
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

//将元素theElement插入到索引theIndex的位置
template <class T>
void doublyLinkedListWithHeader<T>::insert(int theIndex, const T &theElement) {
    //先检查索引是否有效
    if(theIndex < 0 || theIndex > listSize){
        //无效索引
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }
    //在前半部分插入
    chainNode<T>* p = headerNode;
    if (theIndex < (listSize / 2)) {
        //找到插入位置的前驱结点
        for(int i = 0; i < theIndex; ++i)
            p = p->next;
    } else {
        //找到插入位置的前驱结点
        chainNode<T>* p = headerNode;
        for(int i = listSize; i >= theIndex; --i)
            p = p->previous;
    }
    p->next = new chainNode<T>(theElement, p, p->next);
    p->next->next->previous = p->next;
    ++listSize;
}

//删除索引为theIndex的元素
template <class T>
void doublyLinkedListWithHeader<T>::erase(int theIndex) {
    //先检查索引是否有效
    if(theIndex < 0 || theIndex > listSize){
        //无效索引
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }
    //在前半部分插入
    chainNode<T> *p = headerNode, *deleteNode;
    if (theIndex < (listSize / 2)) {
        //找到插入位置的前驱结点
        for(int i = 0; i < theIndex; ++i)
            p = p->next;
        deleteNode = p->next;
    } else {
        //找到插入位置的前驱结点
        chainNode<T>* p = headerNode;
        for(int i = listSize; i >= theIndex; --i)
            p = p->previous;
        deleteNode = p->next;
    }
    p->next = p->next->next;
    p->next->previous = p;
    delete deleteNode;
    --listSize;
}

//首插入
template <class T>
void doublyLinkedListWithHeader<T>::push_front(const T &theElement) {
    //空表
    if (headerNode->next == headerNode) {
        headerNode->next = new chainNode<T>(theElement, headerNode, headerNode);
        headerNode->previous = headerNode->next;
    } else {
        //非空
        headerNode->next = new chainNode<T>(theElement, headerNode, headerNode->next);
        headerNode->next->next->previous = headerNode->next;
    }
    ++listSize;
}

//尾插入
template <class T>
void doublyLinkedListWithHeader<T>::push_back(const T &theElement) {
    //空表
    if (headerNode->next == headerNode) {
        headerNode->next = new chainNode<T>(theElement, headerNode, headerNode);
        headerNode->previous = headerNode->next;
    } else {
        headerNode->previous = new chainNode<T>(theElement, headerNode->previous, headerNode);
        headerNode->previous->previous->next = headerNode->previous;
    }
    ++listSize;
}

//首弹出
template <class T>
void doublyLinkedListWithHeader<T>::pop_front() {
    //空表，直接退出
    if (headerNode->next == headerNode)
        return;

    chainNode<T>* deleteNode = headerNode->next;
    //只有一个结点
    if (deleteNode == headerNode->previous) {
        headerNode->next = headerNode;
        headerNode->previous = headerNode;
    } else {
        headerNode->next = deleteNode->next;
        deleteNode->next->previous = headerNode;
    }
    delete deleteNode;
    --listSize;
}

//尾弹出
template <class T>
void doublyLinkedListWithHeader<T>::pop_back() {
    //空表，直接退出
    if (headerNode->next == headerNode)
        return;

    chainNode<T>* deleteNode = headerNode->previous;
    //只有一个结点
    if (deleteNode == headerNode->next) {
        headerNode->next = headerNode;
        headerNode->previous = headerNode;
    } else {
        headerNode->previous = deleteNode->previous;
        deleteNode->previous->next = headerNode;
    }
    delete deleteNode;
    --listSize;
}

//将元素插入到输出流
template <class T>
void doublyLinkedListWithHeader<T>::output(ostream &out) const {
    for(chainNode<T>* currentNode = headerNode->next; currentNode != headerNode; currentNode = currentNode->next)
        out << currentNode->element << " ";
}

//重载<<运算符
template <class T>
ostream& operator<<(ostream& out, const doublyLinkedListWithHeader<T>& theList) {
    theList.output(out);
    return out;
}

//反转链表
template <class T>
void doublyLinkedListWithHeader<T>::reverse() {
    //交换headerNode的两个指针
    chainNode<T>* p = headerNode;
    while(p->previous != headerNode) {
        chainNode<T>* copyNode = p->next;
        p->next = p->previous;
        p->previous = copyNode;
        p = p->next;
    }
    chainNode<T>* copyNode = p->next;
    p->next = p->previous;
    p->previous = copyNode;
    p = p->next;
}

//交换两个链表
template <class T>
void doublyLinkedListWithHeader<T>::swap(doublyLinkedListWithHeader<T> &theList) {
    //交换两个链表的headerNode
    chainNode<T>* copyNode = headerNode;
    headerNode = theList.headerNode;
    theList.headerNode = copyNode;



    //交换链表长度
    int copySize = listSize;
    listSize = theList.listSize;
    theList.listSize = copySize;
}

//清表
template <class T>
void doublyLinkedListWithHeader<T>::clear() {
    //删除所有结点
    while (headerNode->next != headerNode) {
        chainNode<T>* deleteNode = headerNode->next;
        headerNode->next = deleteNode->next;
        deleteNode->next->previous = headerNode;
        delete deleteNode;
    }
    listSize = 0;
}

//删索引fromIndex至toIndex之间的元素
template <class T>
void doublyLinkedListWithHeader<T>::removeRange(int fromIndex, int toIndex) {
    //确定索引是否有效
    if(fromIndex < 0 || toIndex >= listSize){
        //无效的索引
        ostringstream s;
        s << "Index  from" << fromIndex << " to " << toIndex << " size = " << listSize;
        throw illegalParameterValue(s.str());
    }
    //从左往右更快找到被删除结点
    if (fromIndex < (listSize - toIndex - 1)) {
        //找到需要删除的起始结点的前驱
        chainNode<T>* p = headerNode;
        for(int i = 0; i < fromIndex; ++i)
            p = p->next;
        //开始删除结点
        for(int i = fromIndex; i <= toIndex; ++i){
            chainNode<T>* deleteNode = p->next;
            p->next = deleteNode->next;
            deleteNode->next->previous = p;
            delete deleteNode;
        }
    } else {
        //从右往左更快找到被删除结点
        //找到需要删除的起始结点的后继
        chainNode<T>* p = headerNode;
        for(int i = listSize - 1; i > toIndex; --i)
            p = p->previous;
        //开始删除结点
        for(int i = toIndex; i >= fromIndex; --i){
            chainNode<T>* deleteNode = p->previous;
            p->previous = deleteNode->previous;
            deleteNode->previous->next = p;
            delete deleteNode;
        }
    }
    listSize -= (toIndex - fromIndex + 1);
}

//判断*this是否和theList相等
template <class T>
bool doublyLinkedListWithHeader<T>::isEqual(const doublyLinkedListWithHeader<T> &theList) const {
    //同一个表，直接返回true
    if(this == &theList)
        return true;
    //长度不等，直接返回false
    if(listSize != theList.listSize)
        return false;

    //从两个方向开始比较
    chainNode<T> *currentFirst = headerNode->next, *currentEnd = headerNode->previous;
    chainNode<T> *anotherFirst = theList.headerNode->next, *anotherEnd = theList.headerNode->previous;
    while (currentFirst != currentEnd){
        //遇到不等的元素
        if(currentFirst->element != anotherFirst->element)
            return false;
        if(currentEnd->element != anotherEnd->element)
            return false;
        currentFirst = currentFirst->next;
        currentEnd = currentEnd->previous;
        anotherFirst = anotherFirst->next;
        anotherEnd = anotherEnd->previous;
    }
    return (currentFirst->element == anotherFirst->element);
}

//重载==运算符
template <class T>
bool operator==(const doublyLinkedListWithHeader<T> &theLeftList, const doublyLinkedListWithHeader<T> &theRightList){
    return theLeftList.isEqual(theRightList);
}

//判断*this是否小于theList
template <class T>
bool doublyLinkedListWithHeader<T>::isLess(const doublyLinkedListWithHeader<T> &theList) const {
    //是同一个线性表
    if(this == &theList)
        return false;

    //比较每一个元素
    chainNode<T> *p = headerNode->next, *q = theList.headerNode->next;
    while(p != headerNode && q != theList.headerNode){
        //当前线性表的元素更小
        if(p->element < q->element)
            return true;
        else if(p->element > q->element)
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
bool operator<(const doublyLinkedListWithHeader<T> &theLeftList, const doublyLinkedListWithHeader<T> &theRightList){
    return theLeftList.isLess(theRightList);
}

#endif //DSACPP_DOUBLYLINKEDLISTWITHHEADER_H
