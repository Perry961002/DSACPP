//
// Created by perry on 2019/11/16.
//

#ifndef DSACPP_DICTIONARY_H
#define DSACPP_DICTIONARY_H

//字典的抽象类
template <class K, class E>
class dictionary {
public:
    virtual ~dictionary() {}

    //字典为空时返回true
    virtual bool empty() const = 0;

    //返回元素个数
    virtual int size() const = 0;

    //返回匹配数对的指针
    virtual std::pair<const K, E>* find(const K&) const = 0;

    //删除匹配的数对
    virtual void erase(const K&) = 0;

    //在字典中插入一个数对
    virtual void insert(const std::pair<const K, E>&) = 0;
};

#endif //DSACPP_DICTIONARY_H
