//
// Created by perry on 2019-09-30.
//

#ifndef DSACPP_VECTORLIST_H
#define DSACPP_VECTORLIST_H

#include "linearList.h"
#include <vector>
#include <sstream>
#include "../MyExceptions.h"

/**
 * 利用vector实现的基于数组的线性表
 */
template <class T>
class vectorList : public linearList<T>{
public:
    // 构造函数，复制函数和析构函数
    vectorList(int initialCapacity = 10);
    vectorList(const vectorList<T>&);
    ~vectorList() {delete element;}

    // ADT方法
    bool empty() const {return element->empty();}
    int size() const {return (int)element->size();}
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(ostream& out) const;

    // 增加的方法
    int capacity() const {return (int) element->capacity();}

    // 线性表的起始和结束位置的迭代器
    typedef typename vector<T>::iterator iterator;
    iterator begin() {return element->begin();}
    iterator end() {return element->end();}

    // 尾插入
    void push_back(const T& theElement) {element->push_back(theElement);}

    // 尾弹出
    void pop_back() {element->pop_back();}

    // 翻转数组
    void reverse() {element->reserve();}

    //交换两个数组
    void swap(vectorList<T>& theList) {element->swap(*theList.element);}

    // 清空数组
    void clear() {element->clear();}

    // 重载[]运算符
    T& operator[](int theIndex){
        checkIndex(theIndex);
        return *(element->begin() + theIndex);
    }

protected:
    void checkIndex(int theIndex) const;
    vector<T>* element;  // 存储线性表元素的向量
};

// 构造函数
template <class T>
vectorList<T>::vectorList(int initialCapacity) {
    if(initialCapacity < 1){
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << "Must be > 0";
        throw illegalParameterValue(s.str());
    }

    //创建容量为0的空向量
    element = new vector<T>;
    // 容量从0增加到initialCapacity
    element->reserve(initialCapacity);
}

// 复制构造函数
template <class T>
vectorList<T>::vectorList(const vectorList<T>& theList) {
    element = new vector<T>(*theList.element);
}

// 检查索引是否有效
template <class T>
void vectorList<T>::checkIndex(int theIndex) const {
    if(theIndex < 0 || theIndex >= element->size()){
        ostringstream s;
        s << "index = " << theIndex << "size = " << element->size();
        throw illegalParameterValue(s.str());
    }
}

// 取得索引theIndex上的元素值
template <class T>
T& vectorList<T>::get(int theIndex) const {
    checkIndex(theIndex);
    return *(element->begin() + theIndex);
}

// 取得元素theElement的索引
template <class T>
int vectorList<T>::indexOf(const T &theElement) const {
    // 不存在则返回 -1

    int theIndex = (int)(find(element->begin(), element->end(), theElement) - element->begin());
    // 尾部的下个位置
    if(theIndex == element->size())
        return -1;
    return theIndex;
}

// 删除索引为theIndex的元素
template <class T>
void vectorList<T>::erase(int theIndex) {
    checkIndex(theIndex);
    element->erase(element->begin() + theIndex);
}

// 在索引为theIndex处插入元素theElement
template <class T>
void vectorList<T>::insert(int theIndex, const T &theElement) {
    if(theIndex < 0 || theIndex > element->size()){
        ostringstream s;
        s << "index = " << theIndex << " szie = " << element->size();
        throw illegalIndex(s.str());
    }
    element->insert(element->begin() + theIndex, theElement);
}

// 把元素插入到输出流
template <class T>
void vectorList<T>::output(ostream &out) const {
    //把元素拷贝到输出流
    copy(element->begin(), element->end(), ostream_iterator<T>(out, " "));
}

// 重载<<运算符
template <class T>
ostream& operator<<(ostream& out, const vectorList<T>& theList){
    theList.output(out);
    return out;
}

#endif //DSACPP_VECTORLIST_H
