//
// Created by perry on 2019/11/21.
//

#ifndef DSACPP_SKIPLIST_H
#define DSACPP_SKIPLIST_H

#include <math.h>
#include "skipNode.h"
#include "dictionary.h"

//跳表
template <class K, class E>
class skipList : public dictionary<K, E> {
public:
    //构造和析构函数
    skipList(K largeKey, int maxPairs, float prob);
    ~skipList();

    //判断是否为空
    bool empty() const { return dSize == 0;}

    //返回数对个数
    int size() const { return dSize;}

    //返回匹配数对的指针
    std::pair<const K, E>* find(const K&) const;

    //删除匹配的数对
    void erase(const K&);

    //在字典中插入一个数对
    void insert(const std::pair<const K, E>&);

private:
    //数据成员
    float cutOff;  //随机数生成器的上限，用于确定被插入结点的层数
    int levels;  //链表的级数
    int dSize;  //数对的个数
    int maxLevel;  //允许的最大链表层数
    K tailKey;  //最大关键字

    skipNode<K, E>* headerNode;  //头结点指针
    skipNode<K, E>* tailNode;  //尾结点指针
    skipNode<K, E>** last;  //last[i] 表示 i 层的最后结点
};

//构造函数
template <class K, class E>
skipList<K, E>::skipList(K largeKey, int maxPairs, float prob) {
    //关键字小于largeKey 且数对个数size最多为maxPairs，0 < prob < 1
    cutOff = prob * RAND_MAX;
    maxLevel = (int) ceil(logf((float) maxPairs) / logf(1 / prob)) - 1;
    levels = 0;  //初始化级数
    dSize = 0;
    tailKey = largeKey;

    //生成头结点、尾结点和数组last
    std::pair<K, E> tailPair;
    tailPair.first = tailKey;
    headerNode = new skipNode<K, E> (tailPair, maxLevel + 1);
    tailNode = new skipNode<K, E> (tailPair, 0);
    last = new skipNode<K, E> *[maxLevel + 1];

    //链表为空，任意级链表的头结点都指向尾结点
    for (int i = 0; i <= maxLevel; ++i)
        headerNode->next[i] = tailNode;
}




#endif //DSACPP_SKIPLIST_H
