//
// Created by perry on 2019/11/21.
//

#ifndef DSACPP_SKIPLIST_H
#define DSACPP_SKIPLIST_H

#include <math.h>
#include <sstream>
#include "skipNode.h"
#include "dictionary.h"
#include "../MyExceptions.h"

//跳表
template <class K, class E>
class skipList : public dictionary<K, E> {
public:
    //构造和析构函数
    skipList(K largeKey, int maxPairs = 10000, float prob = 0.5);
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

    //将数对插入到输出流中
    void output(std::ostream& out) const;

public:
    class iterator;  //前向迭代器

    //begin和end方法
    iterator begin() { return iterator(headerNode->next[0]);}
    iterator end() { return iterator(tailNode);}

private:
    //级的分配方法
    int level() const;

    //搜索并把在每一级链表搜索时遇到的最后一个结点存储起来
    skipNode<K, E>* search(const K&) const;

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

//析构函数
template <class K, class E>
skipList<K, E>::~skipList() {
    //删除所有结点和数组

    skipNode<K, E>* nextNode;
    //从headerNode开始，延数对链的方向删除
    while (headerNode != tailNode) {
        nextNode = headerNode->next[0];
        delete headerNode;
        headerNode = nextNode;
    }

    delete tailNode;
    delete [] last;
}

//前向迭代器
template <class K, class E>
class skipList<K, E>::iterator {
public:
    typedef forward_iterator_tag iterator_category;  //向前迭代器
    typedef std::pair<const K, E> value_type;  //迭代器指向的数据类型
    typedef std::pair<const K, E>* pointer;  //指针
    typedef std::pair<const K, E>& reference;  //引用

    //构造函数
    iterator(skipNode<K, E>* theNode = NULL) { node = theNode;}

    //解引用操作符
    std::pair<const K, E>& operator*() { return node->element;}
    std::pair<const K, E>* operator->() { return &node->element;}

    //迭代器加法操作
    iterator& operator++() {node = node->next[0]; return *this;}  //前加
    iterator operator++(int){  //后加
        iterator old = *this;
        node = node->next[0];
        return old;
    }

    //相等检验
    bool operator!=(const iterator right) const {return node != right.node;}
    bool operator==(const iterator right) const {return node == right.node;}
private:
        skipNode<K, E>* node;  //指向跳表结点的指针
    };

//返回匹配数对的指针
template <class K, class E>
std::pair<const K, E>* skipList<K, E>::find(const K &theKey) const {
    //从最高级链表开始查找，在每一级链表中，从左边尽可能逼近要查找的记录

    //没有可能匹配的数对
    if (theKey >= tailKey)
        return NULL;

    //位置beforeNode是关键字为theKey的结点之前最右边的位置
    skipNode<K, E>* beforeNode = headerNode;
    for (int i = levels; i >= 0; --i) {
        //自上而下追踪 i 级链表指针
        while (beforeNode->next[i]->element.first < theKey)
            beforeNode = beforeNode->next[i];
    }

    //检查下一个结点的关键字是否是theKey
    if (beforeNode->next[0]->element.first == theKey)
        return &beforeNode->next[0]->element;

    return NULL;  //没有匹配的数对
}

//确定新插入的结点分配到哪一级
template <class K, class E>
int skipList<K, E>::level() const {
    //返回一个表示链表级的随机数，这个数不大于maxLevel
    int lev = 0;
    while (rand() <= cutOff)
        ++lev;
    return (lev <= maxLevel) ? lev : maxLevel;
}

//搜索并把在每一级链表搜索时遇到的最后一个结点存储起来
template <class K, class E>
skipNode<K, E>* skipList<K, E>::search(const K &theKey) const {
    //位置beforeNode是关键字为theKey的结点之前最右边的位置
    skipNode<K, E>* beforeNode = headerNode;
    for (int i = levels; i >= 0; --i) {
        //自上而下追踪 i 级链表指针
        while (beforeNode->next[i]->element.first < theKey)
            beforeNode = beforeNode->next[i];
        last[i] = beforeNode;  //存储搜索 i 级链表时遇到的最后一个结点
    }
    return beforeNode->next[0];
}

//跳表的插入
template <class K, class E>
void skipList<K, E>::insert(const std::pair<const K, E> &thePair) {
    //关键字太大
    if (thePair.first >= tailKey) {
        std::ostringstream s;
        s << "Key = " << thePair.first << " Must be < " << tailKey;
        throw illegalParameterValue(s.str());
    }

    //查看和插入数对相同关键字的数对是否已经存在
    skipNode<K, E>* theNode = search(thePair.first);
    if (theNode->element.first == thePair.first) {
        //已经存在，则更新数对的值
        theNode->element.second = thePair.second;
        return;
    }

    //如果不存在，则确定新结点所在的级链表
    int theLevel = level();  //新结点的级
    //保证级theLevel <= levels + 1
    if (theLevel > levels) {
        theLevel = ++levels;
        last[theLevel] = headerNode;
    }

    //在结点theNode之后插入新结点
    skipNode<K, E>* newNode = new skipNode<K, E> (thePair, theLevel + 1);
    for (int i = 0; i <= theLevel; ++i) {
        //自下而上，插入i级链表
        newNode->next[i] = last[i]->next[i];
        last[i]->next[i] = newNode;
    }

    ++dSize;
    return;
}

//删除跳表的记录
template <class K, class E>
void skipList<K, E>::erase(const K &theKey) {
    //关键字太大
    if (theKey >= tailKey)
        return;

    //查看是否存在关键字匹配的数对
    skipNode<K, E>* theNode = search(theKey);
    if (theNode->element.first != theKey)
        //不存在
        return;

    //从跳表中删除结点
    for (int i = 0; i <= levels && last[i]->next[i] == theNode; ++i)
        last[i]->next[i] = theNode->next[i];

    //更新链表级
    while (levels > 0 && headerNode->next[levels] == tailNode)
        --levels;

    delete theNode;
    --dSize;
}

//将数对插入到输出流
template <class K, class E>
void skipList<K, E>::output(std::ostream &out) const {
    //遍历0级链表
    for (skipNode<K, E>* currentNode = headerNode->next[0]; currentNode != tailNode;
        currentNode = currentNode->next[0])
        out << "<" << currentNode->element.first << ", " << currentNode->element.second << "> ";
}

//重载<<运算符
template <class K, class E>
ostream& operator<<(ostream& out, const skipList<K, E>& x) {
    x.output(out);
    return out;
}

#endif //DSACPP_SKIPLIST_H
