//
// Created by perry on 2019-10-10.
//

#ifndef DSACPP_CHAINNODE_H
#define DSACPP_CHAINNODE_H

template <class T>
struct chainNode{
    //数据成员
    T element;
    chainNode<T> *next;

    //构造方法
    chainNode() {}
    chainNode(const T& element) {this->element = element;}
    chainNode(const T& element, chainNode<T>* next) {
        this->element = element;
        this->next = next;
    }
};

#endif //DSACPP_CHAINNODE_H
