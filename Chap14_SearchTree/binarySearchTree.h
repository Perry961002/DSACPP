//
// Created by perry on 2019/12/12.
//

#ifndef DSACPP_BINARYSEARCHTREE_H
#define DSACPP_BINARYSEARCHTREE_H

#include <utility>
#include <iostream>
#include "bsTree.h"
#include "linkedBinaryTree.h"

//二叉搜索树
template <class K, class E>
class binarySearchTree : public bsTree<K, E>, public linkedBinaryTree<std::pair<const K, E>> {
public:
    //判断是否为空
    bool empty() const { return this->treeSize == 0;}

    //返回数对的个数
    int size() const { return this->treeSize;}

    //按关键字查找
    std::pair<const K, E>* find(const K&) const;

    //删除匹配的数对
    void erase(const K&);

    //在字典中插入一个数对
    void insert(const std::pair<const K, E>&);

    //按升序输出
    void ascend();

    typedef std::pair<const K, E> pairType;
};

//按升序输出
template <class K, class E>
void binarySearchTree<K, E>::ascend() {
    this->inOrder([] (binaryTreeNode<pairType>* t) {
        if (t != NULL) std::cout << t->element.first << " " << t->element.second << std::endl;
    });
}

//按关键字查找
template <class K, class E>
std::pair<const K, E>* binarySearchTree<K, E>::find(const K &theKey) const {
    //从根结点开始，寻找关键字等于theKey的元素
    binaryTreeNode<pairType> *p = this->root;
    while (p != NULL) {
        //检查p->element的关键字
        if (theKey == p->element.first)  //找到匹配的元素
            return &p->element;
        else if (theKey < p->element.first)  //迭代进入左子树
            p = p->leftChild;
        else  //迭代进入左子树
            p = p->rightChild;
    }

    //没有匹配的数对
    return NULL;
}

//插入数对
template <class K, class E>
void binarySearchTree<K, E>::insert(const std::pair<const K, E> &thePair) {
    //寻找合适的插入位置，和这个位置的父结点
    binaryTreeNode<pairType> *p = this->root, *pp = NULL;
    while (p != NULL) {
        pp = p;  //保护下一层的父结点
        if (thePair.first == p->element.first) {
            //覆盖旧的值
            p->element.second = thePair.second;
            return;
        }
        //p 进入对应的孩子结点继续寻找
        else if (thePair.first < p->element.first)
            p = p->leftChild;
        else
            p = p->rightChild;
    }

    //需要新插入一个结点
    binaryTreeNode<pairType> *newNode = new binaryTreeNode<pairType> (thePair);
    if (this->root == NULL)  //插入空树
        this->root = newNode;
    else {
        if (thePair.first < pp->element.first)
            pp->leftChild = newNode;
        else
            pp->rightChild = newNode;
    }

    ++(this->treeSize);
}

//删除数对
template <class K, class E>
void binarySearchTree<K, E>::erase(const K &theKey) {
    //寻找关键字和它的父结点
    binaryTreeNode<pairType> *p = this->root, *pp = NULL;
    while (p != NULL && theKey != p->element.first) {
        pp = p;  //保护下一层的父结点
        if (theKey < p->element.first)
            p = p->leftChild;
        else
            p = p->rightChild;
    }

    //关键字theKey不存在
    if (p == NULL) return;

    //p的两个孩子都存在
    if (p->leftChild != NULL && p->rightChild != NULL) {
        //寻找p的直接前驱，即p的左子树的最右端结点
        binaryTreeNode<pairType> *s = p->leftChild, *ps = p;  //ps是s的父结
        while (s->rightChild != NULL) {
            ps = s;
            s = s->rightChild;
        }

        //用s的元素值来新建一个替换p的结点
        binaryTreeNode<pairType> *q = new binaryTreeNode<pairType> (s->element, p->leftChild, p->rightChild);
        //用q来替换p的位置
        if (pp == NULL) this->root = q;
        else if (p == pp->leftChild)
            pp->leftChild = q;
        else
            pp->rightChild = q;

        //s就是p的左孩子
        if (ps == p)
            pp = q;
        else
            pp = ps;  //用来后面把s的左孩子变成ps的右孩子
        delete p;
        p = s;  //用来后面把s的左孩子变成ps的右孩子
    }

    //p最多只有一个孩子
    //用c保存孩子指针
    binaryTreeNode<pairType> *c;
    if (p->leftChild != NULL)
        c = p->leftChild;
    else
        c = p->rightChild;

    //删除p
    if (p == this->root)
        this->root = c;
    else {
        if (p == pp->leftChild)
            pp->leftChild = c;
        else
            pp->rightChild = c;
    }
    delete p;
    --(this->treeSize);
}

#endif //DSACPP_BINARYSEARCHTREE_H
