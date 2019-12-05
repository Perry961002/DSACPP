//
// Created by perry on 2019/12/5.
//

#ifndef DSACPP_HEAPSORT_H
#define DSACPP_HEAPSORT_H

#include "maxHeap.h"

//堆排序算法，排序a[1:n]
template <class T>
void heapSort(T a[], int n) {
    maxHeap<T> heap(1);
    heap.initialize(a, n);
    //逐个从大根堆中提取最大值
    for (int i = n; i >= 1; --i)
        heap.pop();

    //在heap析构之前保护a
    heap.deactivateArray();
}

#endif //DSACPP_HEAPSORT_H
