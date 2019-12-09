//
// Created by perry on 2019/12/9.
//

#ifndef DSACPP_minHeap_H
#define DSACPP_minHeap_H

#include <sstream>
#include <algorithm>
#include "maxPriorityQueue.h"
#include "../Chap5_ArrayList/changeLength1D.h"
#include "../MyExceptions.h"

//大根堆
template <class T>
class minHeap : public maxPriorityQueue<T> {
public:
    //构造和析构函数
    minHeap(int initialCapacity = 10);
    ~minHeap() { delete[] heap;}

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

    //将heap置为NULL
    void deactivateArray() { heap = NULL; arrayLength = heapSize = 0;}

private:
    T *heap;  //元素数组，逻辑上的完全二叉树
    int arrayLength;  //数组容量
    int heapSize;  //元素个数
};

//构造函数
template <class T>
minHeap<T>::minHeap(int initialCapacity) {
    if (initialCapacity < 1) {
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }

    arrayLength = initialCapacity + 1;  //元素从下标为1的地方开始存放
    heap = new T[arrayLength];
    heapSize = 0;
}

//初始化一个大根堆,theHeap[1:theSize]
template <class T>
void minHeap<T>::initialize(T *theHeap, int theSize) {
    //重置heap数组
    delete[] heap;
    heap = theHeap;
    heapSize = theSize;
    arrayLength = heapSize + 1;

    //按大根堆的性质进行初始化，从最后一个有子结点的结点开始自下而上的遍历
    for (int root = heapSize / 2; root >= 1; --root) {
        //维护以root为根的树具有大根堆的性质
        T rootElement = heap[root];

        //为rootElement寻找位置
        int child = root * 2;  //child的双亲是rootElement的位置
        while (child <= heapSize) {
            //让child成为两个子结点中较小者的下标
            if (child < heapSize && heap[child] > heap[child + 1])
                ++child;

            //需要把theElement换到heap[child / 2]
            if (rootElement <= heap[child])
                break;

            //不需要交换
            heap[child / 2] = heap[child];  //把孩子上移
            child *= 2;  //移到下一层
        }
        heap[child / 2] = rootElement;
    }
}

//对队首元素的引用
template <class T>
const T& minHeap<T>::top() {
    if (heapSize == 0)
        //堆为空
        throw queueEmpty();

    return heap[1];
}

//插入元素
template <class T>
void minHeap<T>::push(const T &theElement) {
    //必要时数组长度加倍
    if (heapSize == arrayLength - 1) {
        changeLength1D(heap, arrayLength, arrayLength * 2);
        arrayLength *= 2;
    }

    //为theElement寻找位置
    //从新的叶子向上移动
    int currentNode = ++heapSize;
    while (currentNode != 1 && heap[currentNode / 2] > theElement) {
        //不能把theElement放在currentNode的位置
        heap[currentNode] = heap[currentNode / 2];  //把原来的双亲下移
        currentNode /= 2;  //currentNode移向双亲
    }

    heap[currentNode] = theElement;
}

//删除最大元素
template <class T>
void minHeap<T>::pop() {
    //如果堆为空，抛出异常
    if (heapSize == 0)
        throw queueEmpty();

    T lastElement = heap[heapSize--];
    //把最大元素交换到heapSize+1的位置
    heap[heapSize + 1] = heap[1];

    //从根开始，为最后一个元素寻找位置
    int currentNode = 1, child = 2;  //child是currentNode的孩子结点
    while (child <= heapSize) {
        //child应该是currentNode的较小的孩子的下标
        if (child < heapSize && heap[child] > heap[child + 1])
            ++child;

        //需要把lastElement放在currentNode的位置
        if (lastElement <= heap[child])
            break;

        //不需要
        heap[currentNode] = heap[child];  //把孩子中的较大者上移，变成双亲
        currentNode = child;  //移到下一层
        child *= 2;
    }
    heap[currentNode] = lastElement;
}

#endif //DSACPP_minHeap_H
