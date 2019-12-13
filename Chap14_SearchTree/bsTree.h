//
// Created by perry on 2019/12/12.
//

#ifndef DSACPP_BSTREE_H
#define DSACPP_BSTREE_H

#include "../Chap10_SkipAndHashTable/dictionary.h"

//二叉搜索树的抽象类
template <class K, class E>
class bsTree : public dictionary<K, E> {
public:
    //按关键字升序输出
    virtual void ascend() = 0;
};


#endif //DSACPP_BSTREE_H
