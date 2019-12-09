//
// Created by perry on 2019/12/9.
//

#ifndef DSACPP_MAXWBLT_H
#define DSACPP_MAXWBLT_H

#include <utility>
#include <algorithm>
#include "../Chap11_BinaryTree/linkedBinaryTree.h"
#include "../MyExceptions.h"
#include "maxPriorityQueue.h"

//最大重量优先左高树
template <class T>
class maxWblt : public maxPriorityQueue<T>, linkedBinaryTree<std::pair<int, T>> {
public:
    //判断是否为空
    bool empty() const { return this->treeSize == 0;}

    //元素个数
    int size() const { return this->treeSize;}

    //队首元素的引用
    const T& top();

    //删除队首
    void pop();

    //添加元素
    void push(const T& theElement);

    //初始化左高树
    void initialize(T *theElements, int theSize);

    //合并另一个棵树
    void meld(maxWblt<T> &theWblt);

    typedef binaryTreeNode<std::pair<int, T>> pairType;
private:
    //合并两棵左高树
    void meld(binaryTreeNode<std::pair<int, T>> *&, binaryTreeNode<std::pair<int, T>> *&);
};

//队列最大元素的引用
template <class T>
const T& maxWblt<T>::top() {
    //如果树为空，则返回异常
    if (this->treeSize == 0)
        throw queueEmpty();

    return this->root->element.second;
}

//私有方法 合并以 x 和 y 为根的左高树，合并后的左高树以 x 为根
template <class T>
void maxWblt<T>::meld(binaryTreeNode<pair<int, T>> *&x, binaryTreeNode<pair<int, T>> *&y) {
    if (y == NULL)  //y为空
        return;
    if (x == NULL) {
        //x为空
        x = y;
        return;
    }

    //保证 x 指向根结点较大的树
    if (x->element.second < y->element.second)
        std::swap(x, y);

    //递归的把 y 合并到 x->rightChild 上
    meld(x->rightChild, y);

    //x 的左子树为空，交换两个子树
    if (x->leftChild == NULL) {
        x->leftChild = x->rightChild;
        x->rightChild = NULL;
        x->element.first = x->leftChild->element.first + 1;  //更新 x 的 w 值
    } else {
        //保证左子树的 w 值为较大的那个
        if (x->leftChild->element.first < x->rightChild->element.first)
            std::swap(x->leftChild, x->rightChild);
        //更新 w 值
        x->element.first = x->leftChild->element.first + x->rightChild->element.first + 1;
    }
}

//公有方法，合并两个最大重量优先的左高树描述的优先队列
template <class T>
void maxWblt<T>::meld(maxWblt<T> &theWblt) {
    //合并两个对象里面的左高树
    meld(this->root, theWblt.root);
    this->treeSize += theWblt.treeSize;
    //theHblt现在是空的
    theWblt.root = NULL;
    theWblt.treeSize = 0;
}

//删除队列的最大元素
template <class T>
void maxWblt<T>::pop() {
    //如果为空，抛出异常
    if (this->treeSize == 0)
        throw queueEmpty();

    //合并root的左右子树并作为新的root
    pairType *left = this->root->leftChild, *right = this->root->rightChild;
    delete this->root;
    this->root = left;
    meld(this->root, right);
    --(this->treeSize);
}

//插入元素theElement
template <class T>
void maxWblt<T>::push(const T &theElement) {
    //建立只有一个结点，并且值是theElement的左高树
    pairType *x = new pairType (std::make_pair(1, theElement));

    //将 x 合并到 root 上
    meld(this->root, x);
    ++(this->treeSize);
}

//初始化一棵重量优先左高树
template <class T>
void maxWblt<T>::initialize(T *theElements, int theSize) {
    //用每个元素值建立出只有一个结点的左高树并放入队列中
    //然后依次弹出队列的前两个进行合并，并重新放入队列，直到队列中只有一个树
    arrayQueue<pairType *> Q(theSize);
    this->erase();  //清空原来的树

    //初始化左高树的森林并放入队列
    for (int i = 1; i <= theSize; ++i)
        Q.push(new pairType(std::make_pair(1, theElements[i])));

    //从队列中重复的弹出两棵树进行合并，然后把新的树重新放入
    while (Q.size() > 1) {
        pairType *b = Q.front();
        Q.pop();
        pairType *c = Q.front();
        Q.pop();
        meld(b, c);
        Q.push(b);
    }

    if (theSize > 0) this->root = Q.front();
    this->treeSize = theSize;
}

#endif //DSACPP_MAXWBLT_H
