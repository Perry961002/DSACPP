//
// Created by perry on 2019/12/2.
//

#ifndef DSACPP_BINARYTREENODE_H
#define DSACPP_BINARYTREENODE_H

//链表二叉树的结点结构
template <class T>
struct binaryTreeNode {
    //结点数据和左右指针
    T element;
    binaryTreeNode<T> *leftChild, *rightChild;

    binaryTreeNode() {leftChild = rightChild = nullptr;}
    binaryTreeNode(const T& theElement) : element(theElement) {
        leftChild = rightChild = nullptr;
    }
    binaryTreeNode(const T& theElement, binaryTreeNode<T> *theLeftChild,
                binaryTreeNode<T> *theRightChild) : element(theElement) {
        leftChild = theLeftChild;
        rightChild = theRightChild;
    }

};

#endif //DSACPP_BINARYTREENODE_H
