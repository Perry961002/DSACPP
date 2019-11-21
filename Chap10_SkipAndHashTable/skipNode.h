//
// Created by perry on 2019/11/21.
//

#ifndef DSACPP_SKIPNODE_H
#define DSACPP_SKIPNODE_H

#include <utility>

//跳表的结点
template <class K, class E>
struct skipNode {
    typedef std::pair<const K, E> pairType;

    pairType element;
    skipNode<K, E> **next;  //指针数组

    //构造函数
    skipNode(const pairType& thePair, int size) : element(thePair) {
        next = new skipNode<K, E>* [size];
    }
};

#endif //DSACPP_SKIPNODE_H
