//
// Created by perry on 2019/11/18.
//

#ifndef DSACPP_SORTEDCHAIN_H
#define DSACPP_SORTEDCHAIN_H

#include <ostream>
#include "dictionary.h"

//字典结点
template <class K, class E>
struct pairNode {
    typedef std::pair<const K, E> pairType;
    pairType element;
    pairNode<K, E>* next;

    pairNode(const pairType& theElement, pairNode<K, E>* theNext) : element(theElement) {
        next = theNext;
    }
};


//用链表描述的已排序字典
template <class K, class E>
class sortedChain : public dictionary<K, E> {
public:
    //构造和析构函数
    sortedChain() { firstNode = NULL; dSize = 0;}
    ~sortedChain();

    //判空
    bool empty() const { return dSize == 0;}

    //返回元素个数
    int size() const { return dSize;}

    //寻找关键字K对应元素值
    std::pair<const K, E>* find(const K&) const;

    //删除关键字K对应的数对
    void erase(const K&);

    //插入数对
    void insert(const std::pair<const K, E>&);

    //将数对插入到输出流
    void output(std::ostream& out) const;

    //重载[]运算符
    std::pair<const K, E>* operator[](const K&);

private:
    pairNode<K, E>* firstNode;  //链表结点
    int dSize;  //链表长度
};

//析构函数
template <class K, class E>
sortedChain<K, E>::~sortedChain() {
    //删除所有工具
    while (firstNode != NULL) {
        pairNode<K, E>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

//重载[]
template <class K, class E>
std::pair<const K, E>* sortedChain<K, E>::operator[](const K &theKey) {
    pairNode<K, E>* currentNode = firstNode;
    //搜索关键字为thekey的数对
    while (currentNode != NULL && currentNode->element.first != theKey)
        currentNode = currentNode->next;

    //判断是否匹配
    if (currentNode != NULL && currentNode->element.first == theKey)
        return &currentNode->element;

    //没有匹配的数对
    return NULL;
}

//寻找关键字对应的数对
template <class K, class E>
std::pair<const K, E>* sortedChain<K, E>::find(const K &thekey) const {
    pairNode<K, E>* currentNode = firstNode;
    //搜索关键字为thekey的数对
    while (currentNode != NULL && currentNode->element.first != thekey)
        currentNode = currentNode->next;

    //判断是否匹配
    if (currentNode != NULL && currentNode->element.first == thekey)
        return &currentNode->element;

    //没有匹配的数对
    return NULL;
}

//插入数对
template <class K, class E>
void sortedChain<K, E>::insert(const std::pair<const K, E> &thePair) {
    pairNode<K, E> *p = firstNode, *tp = NULL;  //tp是p的前驱结点

    //找到第一个关键字不小于所给数对关键字的结点
    while (p != NULL && p->element.first < thePair.first) {
        tp = p;
        p = p->next;
    }

    //检查是否有匹配的数对
    if (p != NULL && p->element.first == thePair.first) {
        //替换旧值
        p->element.second = thePair.second;
        return;
    }

    //插入新的结点
    pairNode<K, E> *newNode = new pairNode<K, E>(thePair, p);

    //插入到tp之后
    if (tp == NULL) firstNode = newNode;
    else tp->next = newNode;

    ++dSize;
}

//删除关键字为K的数对
template <class K, class E>
void sortedChain<K, E>::erase(const K &theKey) {
    pairNode<K, E> *p = firstNode, *tp = NULL;  //tp是p的前驱结点

    //找到第一个关键字不小于所给数对关键字的结点
    while (p != NULL && p->element.first < theKey) {
        tp = p;
        p = p->next;
    }

    //检查是否有匹配的数对
    if (p != NULL && p->element.first == theKey) {
        //从链表删除结点
        if (tp == NULL) firstNode = p->next;  //p是第一个结点
        else tp->next = p->next;

        delete p;
        --dSize;
    }
}

//将数对插入到输出流
template <class K, class E>
void sortedChain<K, E>::output(std::ostream &out) const {
    pairNode<K, E>* currentNode = firstNode;
    //搜索关键字为thekey的数对
    while (currentNode != NULL) {
        out << "<" << currentNode->element.first << ", " << currentNode->element.second << "> ";
        currentNode = currentNode->next;
    }
}

//重载<<运算符
template <class K, class E>
std::ostream& operator<<(std::ostream& out, const sortedChain<K, E>& theChain) {
    theChain.output(out);
    return out;
}

#endif //DSACPP_SORTEDCHAIN_H
