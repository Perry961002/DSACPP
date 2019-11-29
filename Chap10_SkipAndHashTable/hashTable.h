//
// Created by perry on 2019/11/28.
//

#ifndef DSACPP_HASHTABLE_H
#define DSACPP_HASHTABLE_H

#include <functional>
#include <ostream>
#include "dictionary.h"
#include "../MyExceptions.h"

//散列表
template <class K, class E>
class hashTable : public dictionary<K, E> {
public:
    //构造和析构函数
    hashTable(int theDivisor = 11);
    ~hashTable() { delete[] table;}

    //判断是否为空
    bool empty() const { return dSize == 0;}

    //返回数对个数
    int size() const { return dSize;}

    //寻找关键字对应的数对
    std::pair<const K, E>* find(const K&) const;

    //删除匹配的数对
    void erase(const K&);

    //在字典中插入一个数对
    void insert(const std::pair<const K, E>&);

    //把数对插入到输出流中
    void output(std::ostream& out) const;

private:
    //寻找关键字对应的下标
    int search(const K&) const;

    //寻找第一个下标在theIndex左边(可循环)，并且是允许被关键字theKey对应的数对替换的桶
    int findFirstUseful(const K &theKey, int theIndex) const;

    //数据成员
    std::pair<const K, E>** table;  //散列表
    std::hash<K> hash;  //把类型K 映射到一个非负整数
    int dSize;  //数对的个数
    int divisor;  //散列函数除数
};

//构造函数
template <class K, class E>
hashTable<K, E>::hashTable(int theDivisor) {
    divisor = theDivisor;
    dSize = 0;

    //分配和初始化散列表数组
    table = new std::pair<const K, E>* [divisor];
    for (int i = 0; i < divisor; ++i)
        table[i] = NULL;
}

//寻找关键字对应的下标
template <class K, class E>
int hashTable<K, E>::search(const K &theKey) const {
    int i = (int)hash(theKey) % divisor;  //起始桶
    int j = i;
    do {
        //table[j]不存在或者符合要求
        if (table[j] == NULL || table[j]->first == theKey)
            return j;
        j = (j + 1) % divisor;  //下一个桶
    } while (j != i);

    return j;  //表满
}

//查找函数
template <class K, class E>
std::pair<const K, E>* hashTable<K, E>::find(const K &theKey) const {
    //搜索散列表
    int b = search(theKey);

    //判断是否匹配
    if (table[b] == NULL || table[b]->first != theKey)
        return NULL;

    return table[b];
}

//插入数对
template <class K, class E>
void hashTable<K, E>::insert(const std::pair<const K, E> &thePair) {
    //搜索散列表
    int b = search(thePair.first);

    //检查匹配的数对是否存在
    if (table[b] == NULL) {
        //没有匹配的数对
        table[b] = new std::pair<const K, E> (thePair);
        ++dSize;
    } else {
        if (table[b]->first == thePair.first)
            //匹配的数对存在，修改table[b]->second
            table[b]->second = thePair.second;
        else
            throw hashTableFull();  //表满
    }
}

//寻找第一个下标在theIndex左边(可循环)，并且是允许被关键字theKey对应的数对替换的桶
template <class K, class E>
int hashTable<K, E>::findFirstUseful(const K &theKey, int theIndex) const {
    int i = (int)hash(theKey) % divisor;  //起始桶
    int j = i;
    do {
        if (j >= theIndex || table[j]->first == theKey)
            return j;
        j = (j + 1) % divisor;
    } while (j != i);
    return j;
}

//删除数对
template <class K, class E>
void hashTable<K, E>::erase(const K &theKey) {
    //从要删除的从下一个位置开始，逐个检查每个桶，确定要移动的元素，直到遇到空桶或者回到删除位置
    int theIndex = search(theKey);

    //没有匹配的数对
    if (table[theIndex] == NULL || table[theIndex]->first != theKey)
        return;

    int i = theIndex, j = (theIndex + 1) % divisor;  //i是当前需要被删除的桶，j用来检查每个桶
    //没有遇到空桶，或者没有回到theIndex
    while (table[j] != NULL && j != theIndex) {
        //允许被插入的位置
        int k = findFirstUseful(table[j]->first, i);
        //k正好是i
        if (k == i) {
            table[i] = table[j];
            i = j;
        }
        j = (j + 1) % divisor;
    }
    table[i] = NULL;
    --dSize;
}

//将数对插入到输出流上
template <class K, class E>
void hashTable<K, E>::output(std::ostream &out) const {
    for (int i = 0; i < divisor; ++i) {
        if (table[i] != NULL)
            out << "<" << table[i]->first << ", " << table[i]->second << "> ";
        else
            cout << "NULL ";
    }
}

//重载<<运算符
template <class K, class E>
std::ostream& operator<<(std::ostream& out, const hashTable<K, E>& x) {
    x.output(out);
    return out;
}

#endif //DSACPP_HASHTABLE_H
