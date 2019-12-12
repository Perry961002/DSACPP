//
// Created by perry on 2019/12/12.
//

#ifndef DSACPP_INDEXBSTREE_H
#define DSACPP_INDEXBSTREE_H

#include "bsTree.h"

//索引二叉搜索树的抽象类
template <class K, class E>
class indexBSTree : public bsTree<K, E> {
public:
    //根据给定的索引，返回对应数对的指针
    virtual std::pair<const K, E>* get(int) const = 0;

    //删除给定索引对应的数对
    virtual void delete(int) = 0;
};

#endif //DSACPP_INDEXBSTREE_H
