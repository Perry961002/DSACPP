//
// Created by perry on 2019-09-04.
//

#ifndef DSACPP_ARRAYLIST_H
#define DSACPP_ARRAYLIST_H

#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include "linearList.h"
#include "changeLength1D.h"
#include "../MyExceptions.h"

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

    //返回指定元素最后出现时的索引
    int lastIndex(const T& theElement) const;

    //尾插入
    void push_back(const T& theElement);

    //尾弹出
    void pop_back();

    //设置大小
    void setSize(int theSize);

    //改变数组的容量为当前容量和theCapacity的较大者
    void reserve(int theCapacity);

    //用元素theElement替换索引为theIndex的元素
    void set(int theIndex, const T& theElement);

    //删除指定范围内的所有元素
    void removeRange(int beginIndex, int endIndex);

    //翻转数组
    void reverse();

    //交换两个数组
    void swap(arrayList<T>& theList);

    //清空数组
    void clear();

    // 判断两个数组是否相等
    bool isEqual(const arrayList<T>& theList) const;

    //判断当前数组是否小于theList数组
    bool isLess(const arrayList<T>& theList) const;

    // 判断当前数组是否大于theList数组
    bool isBigger(const arrayList<T>& theList) const;

    //设置表的大小，用在第7章的稀疏矩阵中
    void reSet(int theSize);

    //重载[]运算符
    T& operator[](int theIndex) {
        //返回数组在索引theIndex上的引用

        //检查索引是否有效
        checkIndex(theIndex);
        return element[theIndex];
    }

protected:
    //若索引theIndex无效，则抛出异常
    void checkIndex(int theIndex) const;

    T* element; //存储线性表元素的一维数组
    int arrayLength;  //一维数组的容量
    int listSize;  //线性表的元素个数
public:
    // 内部类, 迭代器，可以随机访问
    class iterator{
    public:
        typedef random_access_iterator_tag iterator_category;  // 随机访问迭代器
        typedef T value_type;  //迭代器指向的数据类型
        typedef ptrdiff_t difference_type; // 标准库里一种与机器相关的数据类型，常用来表示两个指针相减的结果
        typedef T* pointer;  //指针
        typedef T& reference;  //引用

        // 构造函数
        iterator(T* thePosition = 0) {position = thePosition;}

        // 解引用操作符，只是调用成员，不会改变值，所以是 const
        T& operator*() const {return *position;}
        T* operator->() const {return &*position;}

        // 迭代器的值增加
        iterator& operator++() {++position; return *this;}  // 前置
        iterator operator++(int){ // 后置
            iterator old = *this;
            ++position;
            return old;
        }
        iterator operator+(int n){
            // +运算符, 实现随机访问
            iterator old = *this;
            old.position += n;
            return old;
        }
        iterator& operator+=(int n){position += n; return *this;}

        // 迭代器减少
        iterator& operator--() {--position; return *this;}  // 前置
        iterator operator--(int){ // 后置
            iterator old = *this;
            --position;
            return old;
        }
        iterator operator-(int n){
            // -运算符，实现随机访问
            iterator old = *this;
            old.position -= n;
            return old;
        }
        iterator& operator-=(int n){position -= n; return *this;}

        // 计算指针之间距离的差值
        difference_type operator-(const iterator& theIterator) const{ return position - theIterator.position;}

        //测试是否相等
        bool operator!=(const iterator right) const {return position != right.position;}
        bool operator==(const iterator right) const {return position == right.position;}
        bool operator<(const iterator right) const {return position < right.position;}
        bool operator<=(const iterator right) const {return position <= right.position;}
        bool operator>(const iterator right) const {return position > right.position;}
        bool operator>=(const iterator right) const {return position >= right.position;}
    protected:
        T* position;  //指向表元素的指针
    };

    // 返回首元素和尾元素下一个位置的迭代器
    iterator begin() {return iterator(element);}
    iterator end() {return iterator(element + listSize);}
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
    //确定索引theIndex在0 和 listSize - 1之间
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

//返回指定元素最后出现时的索引
template <class T>
int arrayList<T>::lastIndex(const T &theElement) const {
    //返回元素theElement最后一次出现时的索引
    //若元素不存在，则返回 -1

    //查找元素theElement
    int i;
    for(i = listSize - 1; i >=0; --i){
        if(element[i] == theElement)
            return i;
    }
    //没有找到
    if(i < 0)
        return -1;
}

template <class T>
void arrayList<T>::erase(int theIndex) {
    // 删除索引theIndex上的元素
    //如果元素不存在，则抛出异常
    checkIndex(theIndex);

    // 索引有效，则把索引大于theIndex的元素都向前移动
    copy(element + theIndex + 1, element + listSize, element + theIndex);

    //调用析构函数
    element[--listSize].~T();
}

template <class T>
void arrayList<T>::insert(int theIndex, const T &theElement) {
    // 在索引 theIndex 的位置上插入元素 theElement

    if(theIndex < 0 || theIndex > listSize){
        //无效的索引
        ostringstream s;
        s << "Index  " << theIndex << " size = " << listSize;
        throw illegalParameterValue(s.str());
    }

    //有效的索引，确定数组是否已满
    if(listSize == arrayLength){
        //数组空间已满。数组长度倍增
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    //把索引 theIndex 之后的元素向右移动一个位置
    copy_backward(element + theIndex, element + listSize, element + listSize + 1);

    element[theIndex] = theElement;
    ++listSize;
}

template <class T>
void arrayList<T>::output(ostream &out) const {
    //把线性表插入到输出流
    copy(element, element + listSize, ostream_iterator<T>(cout, " "));
}

//重载 <<
template <class T>
ostream& operator<<(ostream& out, const arrayList<T>& x){
    x.output(out);
    return out;
}

//尾插法
template <class T>
void arrayList<T>::push_back(const T &theElement) {
    //有效的索引，确定数组是否已满
    if(listSize == arrayLength){
        //数组空间已满。数组长度倍增
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }
    element[listSize++] = theElement;
}

//尾弹出
template <class T>
void arrayList<T>::pop_back() {
    element[--listSize].~T();
}

//设置数组大小
template <class T>
void arrayList<T>::setSize(int theSize) {
    //如果数组的初始大小小于等于指定的值，则不增加元素
    //如果数组的初始大小大于指定的值，则删除多余元素
    if(theSize < 0){
        ostringstream s;
        s << "Set size = " << theSize << "Must be >= 0";
        throw illegalParameterValue(s.str());
    }
    if(listSize > theSize){
        while(listSize > theSize)
            element[--listSize].~T();
    }
}

//改变数组的容量为当前容量和theCapacity的较大者
template <class T>
void arrayList<T>::reserve(int theCapacity) {
    if(theCapacity > arrayLength){
        changeLength1D(element, arrayLength, theCapacity);
        arrayLength = theCapacity;
    }
}

//用元素theElement替换索引为theIndex的元素
template <class T>
void arrayList<T>::set(int theIndex, const T& theElement) {
    //超出索引，则抛出异常
    checkIndex(theIndex);
    element[theIndex] = theElement;
}

//删除指定范围内的所有元素
template <class T>
void arrayList<T>::removeRange(int beginIndex, int endIndex) {
    //确定索引是否有效
    if(beginIndex < 0 || endIndex >= listSize){
        //无效的索引
        ostringstream s;
        s << "Index  from" << beginIndex << " to " << endIndex << " size = " << listSize;
        throw illegalParameterValue(s.str());
    }
    copy(element + endIndex + 1, element + listSize, element + beginIndex);
    setSize(listSize - (endIndex - beginIndex + 1));
}

//翻转数组
template <class T>
void arrayList<T>::reverse() {
    int i = 0, j = listSize - 1;
    while(i < j){
        if(element[i] != element[j]){
            //swap(element[i], element[j]);
            T temp = element[i];
            element[i] = element[j];
            element[j] = temp;
        }
        ++i;
        --j;
    }
}

//交换两个数组
template <class T>
void arrayList<T>::swap(arrayList<T> &theList) {
    //如果当前数组的容量更大，则将theList扩容
    if(arrayLength > theList.arrayLength)
        theList.reserve(arrayLength);
    else
        reserve(theList.arrayLength);
    for(int i = 0; i < max(listSize, theList.listSize); ++i){
        T temp = element[i];
        element[i] = theList.element[i];
        theList.element[i] = temp;
    }
    int temp = listSize;
    listSize = theList.listSize;
    theList.listSize = temp;
}

//清空数组
template <class T>
void arrayList<T>::clear() {
    while(listSize > 0)
        element[--listSize].~T();
}

// 判断是否相等
template <class T>
bool arrayList<T>::isEqual(const arrayList<T> &theList) const{
    //返回是否和theList相等
    //数组长度相同，且每个元素都相等
    if(this == &theList)
        return true;
    if(listSize != theList.listSize)
        return false;
    int i = 0, j = 0;
    while(i < listSize && j < theList.listSize){
        if(element[i] != theList.element[j])
            return false;
        ++i;
        ++j;
    }
    return true;
}

// 重载==运算符
template <class T>
bool operator==(const arrayList<T>& theLeftList, const arrayList<T>& theRightList){
    return theLeftList.isEqual(theRightList);
}

// 重载 != 运算符
template <class T>
bool operator!=(const arrayList<T>& theLeftList, const arrayList<T>& theRightList){
    return !theLeftList.isEqual(theRightList);
}

// 判断当前数组是否小于theList
template <class T>
bool arrayList<T>::isLess(const arrayList<T> &theList) const{
    if(this == &theList)
        return false;
    //字典序的小于
    int i = 0, j = 0;
    while(i < listSize && j < theList.listSize){
        if(element[i] == theList.element[j]){
            ++i;
            ++j;
        }else if(element[i] < theList.element[j]){
            return true;
        }else
            return false;
    }
    if(i < j)
        return true;
    else
        return false;
}

// 重载<运算符
template <class T>
bool operator<(const arrayList<T>& theLeftList, const arrayList<T>& theRightList){
    return theLeftList.isLess(theRightList);
}

// 重载 >= 运算符
template <class T>
bool operator>=(const arrayList<T>& theLeftList, const arrayList<T>& theRightList){
    return !theLeftList.isLess(theRightList);
}

// 判断当前数组是否大于theList数组
template <class T>
bool arrayList<T>::isBigger(const arrayList<T> &theList) const{
    if(this == &theList)
        return false;
    //字典序的小于
    int i = 0, j = 0;
    while(i < listSize && j < theList.listSize){
        if(element[i] == theList.element[j]){
            ++i;
            ++j;
        }else if(element[i] > theList.element[j]){
            return true;
        }else
            return false;
    }
    if(i > j)
        return true;
    else
        return false;
}

// 重载 > 运算符
template <class T>
bool operator>(const arrayList<T>& theLeftList, const arrayList<T>& theRightList){
    return theLeftList.isBigger(theRightList);
}

//重载 <= 运算符
template <class T>
bool operator<=(const arrayList<T>& theLeftList, const arrayList<T>& theRightList){
    return !theLeftList.isBigger(theRightList);
}

//设置表的大小，用在第7章的稀疏矩阵中
template <class T>
void arrayList<T>::reSet(int theSize) {
    if (theSize < 0) {
        ostringstream s;
        s << "Requested size = " << theSize << " Must be >= 0";
        throw illegalParameterValue(s.str());
    }
    if (theSize > arrayLength) {
        delete element;
        element = new T[theSize];
        arrayLength = listSize;
    }
    listSize = theSize;
}

#endif //DSACPP_ARRAYLIST_H
