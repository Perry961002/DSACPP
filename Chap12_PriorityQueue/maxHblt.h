//
// Created by perry on 2019/12/6.
//

#ifndef DSACPP_MAXHBLT_H
#define DSACPP_MAXHBLT_H

#include <utility>
#include <algorithm>
#include "../Chap11_BinaryTree/linkedBinaryTree.h"
#include "../MyExceptions.h"
#include "maxPriorityQueue.h"

//左高树
template <class T>
class maxHblt : public maxPriorityQueue<T>, linkedBinaryTree<std::pair<int, T>> {
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
    void meld(maxHblt<T> &theHblt);

    typedef binaryTreeNode<std::pair<int, T>> pairType;
private:
    //合并两棵左高树
    void meld(binaryTreeNode<std::pair<int, T>> *&, binaryTreeNode<std::pair<int, T>> *&);
};

//返回最大元素的引用
template <class T>
const T& maxHblt<T>::top() {
    if (this->treeSize == 0)
        throw queueEmpty();

    return this->root->element.second;
}

//私有方法 合并两棵左高树
template <class T>
void maxHblt<T>::meld(binaryTreeNode<pair<int, T>> *&x, binaryTreeNode<pair<int, T>> *&y) {
    //合并以 x 和 y 为根的两棵左高树，合并后的左高树以 x 为根
    if (y == NULL) return;
    if (x == NULL) { x = y; return;}

    //保证 x 是根结点的较大者
    if (x->element.second < y->element.second)
        std::swap(x, y);

    //递归的把 y 合并到 x->rightChild
    meld(x->rightChild, y);

    //如果 x 是叶子结点的话，现在 x 不是左高树，需要交换 x 的左右子结点
    if (x->leftChild == NULL) {
        x->leftChild = x->rightChild;
        x->rightChild = NULL;
        x->element.first = 1;  //因为 x->rightChild 的 s 值是 0
    } else {
        //保证 x->leftChild 的 s 值是较大的
        if (x->leftChild->element.first < x->rightChild->element.first)
            std::swap(x->leftChild, x->rightChild);

        //更新 x 的 s 值
        x->element.first = x->rightChild->element.first + 1;  //左高树的右子树的 s 值 是较小的那个
    }
}

//公有方法 合并另一颗左高树到*this上
template <class T>
void maxHblt<T>::meld(maxHblt<T> &theHblt) {
    //合并两个对象里面的左高树
    meld(this->root, theHblt.root);
    this->treeSize += theHblt.treeSize;
    //theHblt现在是空的
    theHblt.root = NULL;
    theHblt.treeSize = 0;
}

//插入元素
template <class T>
void maxHblt<T>::push(const T &theElement) {
    //建立只有一个结点，并且值是theElement的左高树
    pairType *x = new pairType (std::make_pair(1, theElement));

    //将 x 合并到 root 上
    meld(this->root, x);
    ++(this->treeSize);
}

//删除最大元素
template <class T>
void maxHblt<T>::pop() {
    if (this->treeSize == 0)
        throw queueEmpty();

    //合并root的左右子树并作为新的root
    pairType *left = this->root->leftChild, *right = this->root->rightChild;
    delete this->root;
    this->root = left;
    meld(this->root, right);
    --(this->treeSize);
}

//初始化
template <class T>
void maxHblt<T>::initialize(T *theElements, int theSize) {
    //用每个元素值建立出只有一个结点的左高树并放入队列中
    //然后依次弹出队列的前两个进行合并，并重新放入队列，直到队列中只有一个树
    arrayQueue<pairType *> Q(theSize);
    this->erase();  //清空原来的树

    //初始化左高树的森林并放入队列
    for (int i = 0; i < theSize; ++i)
        Q.push(new pairType(std::make_pair(1, theElements[i])));

    //从队列中重复的弹出两棵树进行合并，然后把新的树重新放入
    while (Q.size() > 1) {
        pairType *b = Q.front();
        Q.pop();
        pairType *c = Q.front();
        Q.front();
        meld(b, c);
        Q.push(b);
    }

    if (theSize > 0) this->root = Q.front();
    this->treeSize = theSize;
}

#endif //DSACPP_MAXHBLT_H
