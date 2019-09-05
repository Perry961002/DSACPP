//
// Created by perry on 2019-09-04.
//

#ifndef DSACPP_ARRAYLIST_H
#define DSACPP_ARRAYLIST_H

#include <iostream>
#include <sstream>
#include "linearList.h"
#include "MyExceptions.h"
using namespace std;

template <class T>
class arrayList : public linearList<T>{
public:
    //构造函数，拷贝构造函数和析构函数
    arrayList(int initialCapacity = 10);
    arrayList(const arrayList<T>&);
    ~arrayList() {delete [] element;};

    //ADT方法
    bool empty() const {return listSize == 0;};
    int size() const {return listSize;};
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(ostream& out) const;

    //其他方法
    //给出数组当前的长度
    int capacity() const {return arrayLength;};

protected:
    //若索引theIndex无效，则抛出异常
    void checkIndex(int theIndex) const;

    T* element; //存储线性表元素的一维数组
    int arrayLength;  //一维数组的容量
    int listSize;  //线性表的元素个数
};

template <class T>
arrayList<T>::arrayList(int initialCapacity) {
    //构造函数
    if(initialCapacity < 1){
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << "Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    element = new T[arrayLength];
    listSize = 0;
}

template <class T>
arrayList<T>::arrayList(const arrayList<T>& theList) {
    //拷贝构造函数
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = new T[arrayLength];
    copy(theList.element, theList.element + listSize, element);
}

template <class T>
void arrayList<T>::checkIndex(int theIndex) const {
    //确定索引theIndex在0 和listSize - 1之间
    if(theIndex < 0 || theIndex >= listSize){
        ostringstream s;
        s << "index = " << theIndex << "size = " << listSize;
        throw illegalParameterValue(s.str());
    }
}

template <class T>
T& arrayList<T>::get(int theIndex) const {
    //返回索引为theIndex的元素
    //若此元素不存在，则抛出异常
    checkIndex(theIndex);
    return element[theIndex];
}

template <class T>
int arrayList<T>::indexOf(const T &theElement) const {
    //返回元素theElement第一次出现时的索引
    //若元素不存在，则返回 -1

    //查找元素theElement
    int theIndex = (int) (find(element, element + listSize, theElement) - element);

    //确定是否找到
    if(theIndex == listSize)
        //没有找到
        return -1;
    else
        return theIndex;
}




#endif //DSACPP_ARRAYLIST_H
