//
// Created by perry on 2019/12/13.
//

#ifndef DSACPP_INDEXBINARYSEARCHTREE_H
#define DSACPP_INDEXBINARYSEARCHTREE_H

#include <utility>
#include "arrayStack.h"
#include "linkedBinaryTree.h"
#include "indexBSTree.h"

//索引二叉搜索树的结点的数值域
template <class K, class E>
struct indexElement {
    int leftSize;
    std::pair<const K, E> element;

    indexElement() : leftSize(0) {}
    indexElement(const std::pair<const K, E> &thePair) : leftSize(0), element(thePair) {}
};

//索引二叉搜索树
template <class K, class E>
class indexBinarySearchTree : public indexBSTree<K, E>, public linkedBinaryTree<indexElement<K, E>> {
public:
    //判断是否为空
    bool empty() const { return this->treeSize == 0;}

    //返回数对的个数
    int size() const { return this->treeSize;}

    //按关键字查找
    std::pair<const K, E>* find(const K&) const;

    //删除匹配的数对
    void erase(const K&) {}

    //在字典中插入一个数对
    void insert(const std::pair<const K, E>&);

    //按升序输出
    void ascend();

    //根据给定的索引，返回对应数对的指针
    virtual std::pair<const K, E>* get(int) const;

    //删除给定索引对应的数对
    virtual void erase(int) {}
};

//按升序输出
template <class K, class E>
void indexBinarySearchTree<K, E>::ascend() {
    this->inOrder([] (binaryTreeNode<indexElement<K, E>>* t) {
        if (t != NULL)
            std::cout << t->element.leftSize << " " << t->element.element.first << " " << t->element.element.second << std::endl;
    });
}

//按关键字查找
template <class K, class E>
std::pair<const K, E>* indexBinarySearchTree<K, E>::find(const K &theKey) const {
    //从根结点开始，寻找关键字等于theKey的元素
    binaryTreeNode<indexElement<K, E>> *p = this->root;
    while (p != NULL) {
        //检查p->element的关键字
        if (theKey == p->element.element.first)  //找到匹配的元素
            return &p->element.element;
        else if (theKey < p->element.element.first)  //迭代进入左子树
            p = p->leftChild;
        else  //迭代进入左子树
            p = p->rightChild;
    }

    //没有匹配的数对
    return NULL;
}

//按索引查找
template <class K, class E>
std::pair<const K, E>* indexBinarySearchTree<K, E>::get(int theIndex) const {
    //如果索引无效
    if (theIndex < 0 || theIndex >= this->treeSize)
        throw illegalIndex("index must be >= 0 and < treeSize");

    //从根结点开始，寻找索引等于theIndex的元素
    binaryTreeNode<indexElement<K, E>> *p = this->root;
    while (p != NULL) {
        //检查p->element的索引
        if (theIndex == p->element.leftSize)  //找到匹配的元素
            return &p->element.element;
        else if (theIndex < p->element.element.first)  //迭代进入左子树，索引不变
            p = p->leftChild;
        else {  //迭代进入右子树，索引改变
            p = p->rightChild;
            theIndex -= (p->element.leftSize + 1);
        }
    }

    //没有匹配的数对
    return NULL;
}

//插入数对
template <class K, class E>
void indexBinarySearchTree<K, E>::insert(const pair<const K, E> &thePair) {
    //寻找合适的插入位置，和这个位置的父结点
    binaryTreeNode<indexElement<K, E>> *p = this->root;
    arrayStack<binaryTreeNode<indexElement<K, E>> *> stack;  //保存搜索路径上经过的结点
    while (p != NULL) {
        stack.push(p);
        if (thePair.first == p->element.element.first) {  //覆盖旧的值
            p->element.element.second = thePair.second;
            return;
        } else if (thePair.first < p->element.element.first)
            p = p->leftChild;
        else
            p = p->rightChild;
    }
    //需要新插入一个结点
    binaryTreeNode<indexElement<K, E>> *newNode = new binaryTreeNode<indexElement<K, E>> (thePair);
    if (this->root == NULL)  //插入空树
        this->root = newNode;
    else {
        p = stack.top(); stack.pop();
        if (thePair.first < p->element.element.first) {
            p->leftChild = newNode;
            p->element.leftSize += 1;
        } else
            p->rightChild = newNode;
    }
    //自底向上更新结点的leftSize
    binaryTreeNode<indexElement<K, E>> *pp;
    while (!stack.empty()) {
        pp = stack.top(); stack.pop();
        if (p == pp->leftChild)
            pp->element.leftSize += 1;
        p = pp;
    }
    ++(this->treeSize);
}



#endif //DSACPP_INDEXBINARYSEARCHTREE_H
