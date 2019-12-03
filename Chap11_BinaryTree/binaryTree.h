//
// Created by perry on 2019/12/2.
//

#ifndef DSACPP_BINARYTREE_H
#define DSACPP_BINARYTREE_H

//二叉树抽象类
template <class T>
class binaryTree {
public:
    virtual ~binaryTree() {}

    //判断二叉树是否为空
    virtual bool empty() const = 0;

    //返回二叉树的元素个数
    virtual int size() const = 0;

    /*
     * 下面是4中遍历方法，参数为函数指针，可以制订访问结点数据时的方法
     */
    //前序遍历
    virtual void preOrder(void (*) (T *)) = 0;

    //中序遍历
    virtual void inOrder(void (*) (T *)) = 0;

    //后序遍历
    virtual void postOrder(void (*) (T *)) = 0;

    //层次遍历
    virtual void levelOrder(void (*) (T *)) = 0;
};

#endif //DSACPP_BINARYTREE_H
