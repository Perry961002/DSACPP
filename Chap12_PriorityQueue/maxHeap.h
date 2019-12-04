//
// Created by perry on 2019/12/4.
//

#ifndef DSACPP_MAXHEAP_H
#define DSACPP_MAXHEAP_H

#include <sstream>
#include "maxPriorityQueue.h"
#include "../Chap5_ArrayList/changeLength1D.h"
#include "../MyExceptions.h"

//大根堆
template <class T>
class maxHeap : public maxPriorityQueue<T> {
public:
    //构造和析构函数
    maxHeap(int initialCapacity = 10);
    ~maxHeap() { delete[] heap;}

    //判空
    bool empty() const { return heapSize == 0;}

    //返回元素个数
    int size() const { return heapSize;}

    //对队首元素的引用
    const T& top();

    //删除队首元素
    void pop();

    //添加元素
    void push(const T&);

    //初始化
    void initialize(T*, int);

private:
    T *heap;  //元素数组，逻辑上的完全二叉树
    int arrayLength;  //数组容量
    int heapSize;  //元素个数
};

//构造函数
template <class T>
maxHeap<T>::maxHeap(int initialCapacity) {
    if (initialCapacity < 1) {
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }

    arrayLength = initialCapacity + 1;  //元素从下标为1的地方开始存放
    heap = new T[arrayLength];
    heapSize = 0;
}

//初始化一个大根堆
template <class T>
void maxHeap<T>::initialize(T *theHeap, int theSize) {
    //重置heap数组
    delete[] heap;
    heap = theHeap;
    heapSize = theSize;

    //按大根堆的性质进行初始化，从最后一个有子结点的结点开始自下而上的遍历
    for (int root = heapSize / 2; root >= 1; --root) {
        //维护以root为根的树具有大根堆的性质
        T rootElement = heap[root];

        //为rootElement寻找位置
        int child = root * 2;  //child的双亲是rootElement的位置
        while (child <= heapSize) {
            //让child成为两个子结点中较大者的下标
            if (child < heapSize && heap[child] < heap[child + 1])
                ++child;

            //需要把theElement换到heap[child / 2]
            if (rootElement >= heap[child])
                break;

            //不需要交换
            heap[child / 2] = heap[child];  //把孩子上移
            child *= 2;  //移到下一层
        }
        heap[child / 2] = rootElement;
    }
}


#endif //DSACPP_MAXHEAP_H
