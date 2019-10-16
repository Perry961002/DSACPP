//
// Created by perry on 2019/10/14.
//

#ifndef DSACPP_EXTENDEDCHAIN_H
#define DSACPP_EXTENDEDCHAIN_H

#include "extendedLinearList.h"
#include "chain.h"

//派生chain类作为抽象类extendedLinearList的链式描述
template <class T>
class extendedChain : public extendedLinearList<T>, public chain<T>{
public:
    //构造函数、复制构造函数
    extendedChain(int initialCapacity = 10) : chain<T>::chain(initialCapacity) {}
    extendedChain(const extendedChain<T>& theList) : chain<T>::chain(theList) {}

    //ADT方法
    bool empty() const {return chain<T>::empty();}
    int size() const {return chain<T>::size();}
    T& get(int theIndex) const {return chain<T>::get(theIndex);}
    int indexOf(const T& theElement) const {return chain<T>::indexOf(theElement);}
    void output(ostream& out) const {chain<T>::output(out);}
    //在后面实现类extenedChain的特殊版本
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    //抽象基类里的纯虚函数
    void clear();
    void push_back(const T& theElement);

    //设置大小
    void setSize(int theSize);

    //首插入
    void push_front(const T& theElement);

    //首弹出
    void pop_front();

    //首元素
    T& front() {return chain<T>::firstNode->element;}

    //尾元素
    T& back() {return lastNode->element;}

    //删除指定范围的元素
    void removeRange(int fromIndex, int toIndex);

    //反转线性表
    void reverse();

    //交换两个线性表
    void swap(extendedChain<T>& theList);

    //父类chain中可直接利用的函数
    void set(int theIndex, const T& theElement) {chain<T>::set(theIndex, theElement);}
    int lastIndexOf(const T& theElement) const {return chain<T>::lastIndexOf(theElement);}

    //利用父类chain来实现自己的函数
    bool isEqual(const extendedChain<T>& theList) const {return chain<T>::isEqual(theList);}
    bool isLess(const extendedChain<T>& theList) const {return chain<T>::isLess(theList);}

    //重载[]运算符
    T& operator[](int theIndex) {
        //检查索引是否有效
        checkIndex(theIndex);
        if(theIndex == 0)
            return chain<T>::firstNode->element;
        else if(theIndex == chain<T>::listSize - 1)
            return lastNode->element;
        else{
            //移向索引为theIndex的结点
            chainNode<T>* currentNode = chain<T>::firstNode;
            for(int i = 0; i < theIndex; ++i)
                currentNode = currentNode->next;
            return currentNode->element;
        }
    }

public:
    //迭代器类，直接使用父类chain的迭代器
    typedef typename chain<T>::iterator iterator;
    //首元素的迭代器
    iterator begin() {return iterator(chain<T>::firstNode);}
    //尾元素下一个位置的迭代器
    iterator end() {return iterator(NULL);}

protected:
    void checkIndex(int theIndex) const {chain<T>::checkIndex(theIndex);}
    chainNode<T>* lastNode;  //尾结点
};

//重载<<运算符
template <class T>
ostream& operator<<(ostream& out, const extendedChain<T>& theList){
    theList.output(out);
    return out;
}

//重载==运算符
template <class T>
bool operator==(const extendedChain<T>& theLeftList, const extendedChain<T>& theRightList){
    return theLeftList.isEqual(theRightList);
}

//重载<运算符
template <class T>
bool operator<(const extendedChain<T>& theLeftList, const extendedChain<T>& theRightList){
    return theLeftList.isLess(theRightList);
}

//删除索引为theIndex的元素
template <class T>
void extendedChain<T>::erase(int theIndex) {
    //如果索引不存在，则抛出异常
    checkIndex(theIndex);

    //找到需要删除的结点
    chainNode<T>* deleteNode;
    if(theIndex == 0){
        //删除首结点
        deleteNode = chain<T>::firstNode;
        chain<T>::firstNode = chain<T>::firstNode->next;
        if(chain<T>::listSize == 1)
            lastNode = NULL;
    } else if(theIndex == chain<T>::listSize - 1){
        //删除最后一个结点
        //找到倒数第二个结点
        chainNode<T>* p = chain<T>::firstNode;
        while(p->next->next != NULL)
            p = p->next;
        deleteNode = p->next;
        lastNode = p;
    } else{
        //删除任意结点
        chainNode<T>* p = chain<T>::firstNode;
        for(int i = 0; i < theIndex - 1; ++i)
            p = p->next;
        deleteNode = p->next;
        p->next = p->next->next;
    }
    --chain<T>::listSize;
    delete deleteNode;
}

//清表
template <class T>
void extendedChain<T>::clear() {
    //删除链表的所有结点
    while(chain<T>::firstNode != NULL){
        chainNode<T>* nextNode = chain<T>::firstNode->next;
        delete chain<T>::firstNode;
        chain<T>::firstNode = nextNode;
    }
    chain<T>::listSize = 0;
}

//设置大小为theSize
template <class T>
void extendedChain<T>::setSize(int theSize) {
    //如果数组的初始大小小于等于指定的值，则增加NULL元素
    //如果数组的初始大小大于指定的值，则删除多余元素
    if(theSize < 0){
        ostringstream s;
        s << "Set size = " << theSize << "Must be >= 0";
        throw illegalParameterValue(s.str());
    }
    if(chain<T>::listSize > theSize){
        //找到索引为theSize的前驱
        chainNode<T>* p = chain<T>::firstNode;
        for(int i = 0; i < theSize - 1; ++i)
            p = p->next;
        //删除所有结点
        while(p->next != NULL){
            chainNode<T>* currentNode = p->next;
            p->next = currentNode->next;
            delete currentNode;
        }
        lastNode = p;
        chain<T>::listSize = theSize;
    }
}

//把元素theElement插入到线性表中索引为theIndeex的地方
template <class T>
void extendedChain<T>::insert(int theIndex, const T &theElement) {
    //先检查索引是否有效
    if(theIndex < 0 || theIndex > chain<T>::listSize){
        //无效索引
        ostringstream s;
        s << "index = " << theIndex << " size = " << chain<T>::listSize;
        throw illegalIndex(s.str());
    }

    if(theIndex == 0) {
        //空表
        if(chain<T>::firstNode == NULL)
            chain<T>::firstNode = lastNode = new chainNode<T>(theElement, NULL);
        else
            //在非空链表头插入
            chain<T>::firstNode = new chainNode<T>(theElement, chain<T>::firstNode);
    }else if(theIndex == chain<T>::listSize)
        this->push_back(theElement);
    else{
        //需要插入索引的前驱
        chainNode<T>* p = chain<T>::firstNode;
        for(int i = 0; i < theIndex - 1; ++i)
            p = p->next;
        p->next = new chainNode<T>(theElement, p->next);
    }
    ++chain<T>::listSize;
}

//尾插入
template <class T>
void extendedChain<T>::push_back(const T &theElement) {
    chainNode<T>* newNode = new chainNode<T>(theElement, NULL);
    if(chain<T>::firstNode == NULL)
        //链表为空
        chain<T>::firstNode = lastNode = newNode;
    else{
        //把新结点附加到lastNode指向的结点
        lastNode->next = newNode;
        lastNode = newNode;
    }
    ++chain<T>::listSize;
}

//首插入
template <class T>
void extendedChain<T>::push_front(const T &theElement) {
    //线性表初始为空
    if(chain<T>::firstNode == NULL)
        chain<T>::firstNode = lastNode = new chainNode<T>(theElement, NULL);
    //初始不为空
    else
        chain<T>::firstNode = new chainNode<T>(theElement, chain<T>::firstNode);
}

//首弹出
template <class T>
void extendedChain<T>::pop_front() {
    chain<T>::pop_front();
    if(chain<T>::firstNode == NULL)
        lastNode = NULL;
}

//删除指定范围内的元素
template <class T>
void extendedChain<T>::removeRange(int fromIndex, int toIndex) {
    //确定索引是否有效
    if(fromIndex < 0 || toIndex >= chain<T>::listSize){
        //无效的索引
        ostringstream s;
        s << "Index  from" << fromIndex << " to " << toIndex << " size = " << chain<T>::listSize;
        throw illegalParameterValue(s.str());
    }
    //找到开始删除结点的前驱结点
    chainNode<T>* p = chain<T>::firstNode;
    for(int i = 0; i < fromIndex - 1; ++i)
        p = p->next;
    int needDeleteNum = (toIndex - fromIndex + 1);
    while(needDeleteNum > 0){
        chainNode<T>* currentNode = p->next;
        p->next = currentNode->next;
        delete currentNode;
        --needDeleteNum;
    }
    //末尾元素也在删除范围里
    if(toIndex == chain<T>::listSize - 1)
        lastNode = p;
    chain<T>::listSize -= (toIndex - fromIndex + 1);
}

//反转线性表
template <class T>
void extendedChain<T>::reverse() {
    //最多只有一个结点的情况下不变
    if(chain<T>::listSize < 2) return;

    chainNode<T>* currentNode = chain<T>::firstNode->next;
    chain<T>::firstNode->next = NULL;
    lastNode = chain<T>::firstNode;
    //迭代
    while(currentNode != NULL){
        chainNode<T>* nextNode = currentNode->next;
        currentNode->next = chain<T>::firstNode;
        chain<T>::firstNode = currentNode;
        currentNode = nextNode;
    }
}

//交换两个线性表
template <class T>
void extendedChain<T>::swap(extendedChain<T> &theList) {
    chain<T>::swap(theList);
    //交换两个lastnode结点
    chainNode<T>* copyChain = theList.lastNode;
    theList.lastNode = lastNode;
    lastNode = copyChain;
}

#endif //DSACPP_EXTENDEDCHAIN_H
