//
// Created by perry on 2019/11/29.
//

#ifndef DSACPP_HASHCHAIN_H
#define DSACPP_HASHCHAIN_H

#include <functional>
#include <ostream>
#include "dictionary.h"
#include "sortedChain.h"

//链表描述的hash表
template <class K, class E>
class hashChain : public dictionary<K, E> {
public:
    //构造和析构函数
    hashChain(int theDivisor = 11);
    ~hashChain() { delete[] table;}

    //判空
    bool empty() const { return dSize == 0;}

    //数对的个数
    int size() const { return dSize;}

    //返回匹配数对的指针
    std::pair<const K, E>* find(const K& theKey) const { return table[hash(theKey) % divisor].find(theKey);}

    //删除匹配的数对
    void erase(const K&);

    //在字典中插入一个数对
    void insert(const std::pair<const K, E>&);

    //把数对插入到输出流中
    void output(std::ostream& out) const;

private:
    sortedChain<K, E>* table;  //hash表
    std::hash<K> hash;  //hash函数
    int dSize;  //数对的个数
    int divisor;  //散列函数除数
};

//构造函数
template <class K, class E>
hashChain<K, E>::hashChain(int theDivisor) {
    divisor = theDivisor;
    dSize = 0;
    table = new sortedChain<K, E> [divisor];
}

//插入数对
template <class K, class E>
void hashChain<K, E>::insert(const std::pair<const K, E> &thePair) {
    int homeBucket = (int) hash(thePair.first) % divisor;
    int homeSize = table[homeBucket].size();
    table[homeBucket].insert(thePair);
    //确定是否插入了新的数对
    if (table[homeBucket].size() > homeSize)
        ++dSize;
}

//删除关键字对应的数对
template <class K, class E>
void hashChain<K, E>::erase(const K &theKey) {
    int homeBucket = (int) hash(theKey) % divisor;
    int homeSize = table[homeBucket].size();
    table[homeBucket].erase(theKey);
    //确定是否插入了新的数对
    if (table[homeBucket].size() < homeSize)
        --dSize;
}

//将数对插入到输出流
template <class K, class E>
void hashChain<K, E>::output(std::ostream &out) const {
    for (int i = 0; i < divisor; ++i) {
        if (table[i].empty())
            std::cout << "NULL ";
        else
            std::cout << table[i];
    }
}

//重载<<运算符
template <class K, class E>
std::ostream& operator<<(std::ostream& out, const hashChain<K, E>& x) {
    x.output(out);
    return out;
}

#endif //DSACPP_HASHCHAIN_H
