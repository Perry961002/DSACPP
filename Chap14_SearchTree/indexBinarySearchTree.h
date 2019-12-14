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
    void erase(const K&);

    //在字典中插入一个数对
    void insert(const std::pair<const K, E>&);

    //按升序输出
    void ascend();

    //根据给定的索引，返回对应数对的指针
    virtual std::pair<const K, E>* get(int) const;

    //删除给定索引对应的数对
    virtual void eraseIndex(int);
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
        else if (theIndex < p->element.leftSize)  //迭代进入左子树，索引不变
            p = p->leftChild;
        else {  //迭代进入右子树，索引改变
            theIndex -= (p->element.leftSize + 1);
            p = p->rightChild;
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

//按关键字删除索引二叉搜索树的数对
template <class K, class E>
void indexBinarySearchTree<K, E>::erase(const K &theKey) {
    //寻找关键字对应的结点
    binaryTreeNode<indexElement<K, E>> *p = this->root, *pp = NULL;
    arrayStack<binaryTreeNode<indexElement<K, E>> *> stack;  //保存搜索路径上经过的结点
    while (p != NULL && theKey != p->element.element.first) {
        pp = p;
        stack.push(p);
        if (theKey < p->element.element.first)
            p = p->leftChild;
        else
            p = p->rightChild;
    }
    //关键字theKey不存在
    if (p == NULL) return;
    //把栈里结点的leftSize更新
    binaryTreeNode<indexElement<K, E>> *deleteA = NULL, *deleteB = p;
    while (!stack.empty()) {
        deleteA = stack.top(); stack.pop();
        if (deleteB == deleteA->leftChild)
            deleteA->element.leftSize -= 1;
        deleteB = deleteA;
    }
    //p的两个孩子都存在
    if (p->leftChild != NULL && p->rightChild != NULL) {
        //寻找p的直接前驱，即p的左子树的最右端结点
        binaryTreeNode<indexElement<K, E>> *s = p->leftChild, *ps = p;  //ps是s的父结
        while (s->rightChild != NULL) {
            ps = s;
            s = s->rightChild;
        }
        //用s的元素值来新建一个替换p的结点
        binaryTreeNode<indexElement<K, E>> *q = new binaryTreeNode<indexElement<K, E>> (s->element, p->leftChild, p->rightChild);
        q->element.leftSize = p->element.leftSize - 1;  //s移到了p的位置上，所以leftSize - 1
        if (pp == NULL) this->root = q;  //删除的是根结点
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
    binaryTreeNode<indexElement<K, E>> *c;  //用c保存孩子指针
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

//按索引删除索引二叉搜索树的数对
template <class K, class E>
void indexBinarySearchTree<K, E>::eraseIndex(int theIndex) {
    //寻找关键字对应的结点
    binaryTreeNode<indexElement<K, E>> *p = this->root, *pp = NULL;
    arrayStack<binaryTreeNode<indexElement<K, E>> *> stack;  //保存搜索路径上经过的结点
    while (p != NULL && theIndex != p->element.leftSize) {
        pp = p;
        stack.push(p);
        if (theIndex < p->element.leftSize)
            p = p->leftChild;
        else {
            theIndex -= (p->element.leftSize + 1);
            p = p->rightChild;
        }
    }
    //关键字theKey不存在
    if (p == NULL) return;

    //把栈里结点的leftSize更新
    binaryTreeNode<indexElement<K, E>> *deleteA = NULL, *deleteB = p;
    while (!stack.empty()) {
        deleteA = stack.top(); stack.pop();
        if (deleteB == deleteA->leftChild)
            deleteA->element.leftSize -= 1;
        deleteB = deleteA;
    }
    //p的两个孩子都存在
    if (p->leftChild != NULL && p->rightChild != NULL) {
        //寻找p的直接前驱，即p的左子树的最右端结点
        binaryTreeNode<indexElement<K, E>> *s = p->leftChild, *ps = p;  //ps是s的父结
        while (s->rightChild != NULL) {
            ps = s;
            s = s->rightChild;
        }

        //用s的元素值来新建一个替换p的结点
        binaryTreeNode<indexElement<K, E>> *q = new binaryTreeNode<indexElement<K, E>> (s->element, p->leftChild, p->rightChild);
        q->element.leftSize = p->element.leftSize - 1;  //s移到了p的位置上，所以leftSize - 1
        if (pp == NULL) this->root = q;  //删除的是根结点
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
    binaryTreeNode<indexElement<K, E>> *c;
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

#endif //DSACPP_INDEXBINARYSEARCHTREE_H
