//
// Created by perry on 2019/12/2.
//

#ifndef DSACPP_LINKEDBINARYTREE_H
#define DSACPP_LINKEDBINARYTREE_H

#include "binaryTreeNode.h"
#include "binaryTree.h"
#include "arrayStack.h"
#include "arrayQueue.h"

//类linkedBinaryTree
template <class E>
class linkedBinaryTree : public binaryTree<binaryTreeNode<E>> {
public:
    //构造和析构函数
    linkedBinaryTree() {root = NULL; treeSize = 0;}
    ~linkedBinaryTree() {erase();}

    //合成二叉树
    void makeTree(const E& theElement, linkedBinaryTree<E>& theLeft, linkedBinaryTree<E>& theRight);

    //判断是否为空
    bool empty() const { return treeSize == 0;}

    //树的结点个数
    int size() const { return treeSize;}

    //前序遍历
    void preOrder(void (*theVisit) (binaryTreeNode<E> *));

    //中序遍历
    void inOrder(void (*theVisit) (binaryTreeNode<E> *));

    //后序遍历
    void postOrder(void (*theVisit) (binaryTreeNode<E> *));

    //层次遍历
    void levelOrder(void (*theVisit) (binaryTreeNode<E> *));

    //求树的高度
    int height() const { return height(root);}

    //清空整个二叉树
    void erase() {
        postOrder(dispose);
        root = NULL; treeSize = 0;
    }

private:
    binaryTreeNode<E> *root;  //指向根结点的指针
    int treeSize;  //树的结点个数
    static void (*visit) (binaryTreeNode<E>*);  //访问函数指针

    //删除结点
    static void dispose(binaryTreeNode<E> *t) {delete t;}

    //求树的高度
    static int height(binaryTreeNode<E> *t);
};

//用于实力化visit
template <class E>
void (*linkedBinaryTree<E>::visit)(binaryTreeNode<E>*);

//合成二叉树
template <class E>
void linkedBinaryTree<E>::makeTree(const E &theElement, linkedBinaryTree<E> &theLeft, linkedBinaryTree<E> &theRight) {
    root = new binaryTreeNode<E> (theElement, theLeft.root, theRight.root);
    treeSize = theLeft.treeSize + theRight.treeSize + 1;

    //释放子树
    theLeft.root = theRight.root = NULL;
    theLeft.treeSize = theRight.treeSize = 0;
}

//前序遍历
template <class E>
void linkedBinaryTree<E>::preOrder(void (*theVisit) (binaryTreeNode<E> *)) {
    //非递归实现
    if (root == NULL)
        return;

    visit = theVisit;
    arrayStack<binaryTreeNode<E>*> s(treeSize);
    binaryTreeNode<E> *p = NULL;
    s.push(root);
    while (!s.empty()) {
        //访问根
        p = s.top();
        s.pop();
        visit(p);
        //按右左的顺序入栈
        if (p->rightChild != NULL)
            s.push(p->rightChild);
        if (p->leftChild != NULL)
            s.push(p->leftChild);
    }
}

//中序遍历
template <class E>
void linkedBinaryTree<E>::inOrder(void (*theVisit) (binaryTreeNode<E> *)) {
    //非递归实现
    if (root == NULL)
        return;

    visit = theVisit;
    arrayStack<binaryTreeNode<E>*> s(treeSize);
    binaryTreeNode<E> *p = root;
    while (p != NULL || !s.empty()) {
        //将最左侧的结点入栈
        if (p != NULL) {
            s.push(p);
            p = p->leftChild;
        } else {
            //访问当前结点并进入右子树
            p = s.top();
            s.pop();
            visit(p);
            p = p->rightChild;
        }
    }
}

//后序遍历
template <class E>
void linkedBinaryTree<E>::postOrder(void (*theVisit) (binaryTreeNode<E> *)) {
    //非递归实现
    if (root == NULL)
        return;

    visit = theVisit;
    arrayStack<binaryTreeNode<E>*> s(treeSize);
    s.push(root);
    //用于后面判断是否可以将栈顶的结点弹出
    binaryTreeNode<E> *pre = NULL;
    binaryTreeNode<E> *cur = NULL;
    while (!s.empty()) {
        cur = s.top();

        //判断是否需要弹出栈顶
        if ((cur->leftChild == NULL && cur->rightChild == NULL) ||
            (pre != NULL && (pre == cur->leftChild || pre == cur->rightChild))) {
            //当当前结点是叶子结点，或者当前结点的左右子树都被访问过的时候弹出
            s.pop();
            visit(cur);
            pre = cur;
        } else {
            //将右左子结点入栈
            if (cur->rightChild != NULL)
                s.push(cur->rightChild);
            if (cur->leftChild != NULL)
                s.push(cur->leftChild);
        }
    }
}

//层次遍历
template <class E>
void linkedBinaryTree<E>::levelOrder(void (*theVisit) (binaryTreeNode<E> *)) {
    //利用队列实现
    if (root == NULL)
        return;

    visit = theVisit;
    //辅助的队列空间
    arrayQueue<binaryTreeNode<E>*> q(treeSize / 2 + 1);
    q.push(root);
    binaryTreeNode<E> *p = NULL;
    while (!q.empty()) {
        p = q.front();
        q.pop();
        visit(p);
        if (p->leftChild != NULL)
            q.push(p->leftChild);
        if (p->rightChild != NULL)
            q.push(p->rightChild);
    }
}

//求树高
template <class E>
int linkedBinaryTree<E>::height(binaryTreeNode<E> *t) {
    //采用中序遍历的方式
    if (t == NULL)
        return 0;
    int h1 = height(t->leftChild);
    int h2 = height(t->rightChild);

    //树的高度等于左右子树高度的最大值 + 1
    return 1 + ((h1 > h2) ? h1 : h2);
}

#endif //DSACPP_LINKEDBINARYTREE_H
