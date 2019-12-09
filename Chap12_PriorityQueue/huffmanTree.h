//
// Created by perry on 2019/12/9.
//

#ifndef DSACPP_HUFFMANTREE_H
#define DSACPP_HUFFMANTREE_H

#include "../Chap11_BinaryTree/binaryTreeNode.h"
#include "minHeap.h"

//huffman树的结点类型
template <class T>
struct huffmanNode {
    binaryTreeNode<int> *tree;  //二叉树的指针
    T weight;  //权重

    //重载()运算符
    operator T () const { return weight;}
};

//构造一棵huffman树
template <class T>
binaryTreeNode<int>* huffmanTree(T weights[], int n) {
    //用权weight[1:n]生成huffman树，n >= 1
    //创建一组单结点树
    huffmanNode<T> *hNode = new huffmanNode<T> [n + 1];
    for (int i = 1; i <= n; ++i) {
        hNode[i].weight = weights[i];
        hNode[i].tree = new binaryTreeNode<int> (i, NULL, NULL);
    }

    //使用一组单结点树构成小根堆
    minHeap<huffmanNode<T>> heap(1);
    heap.initialize(hNode, n);

    //不断从小根堆中提取两个树进行合并，直到只剩下一棵树
    huffmanNode<T> w, x, y;
    binaryTreeNode<int> *z;
    while (heap.size() > 1) {
        //从小根堆中提取两棵最轻的树
        x = heap.top(); heap.pop();
        y = heap.top(); heap.pop();

        //合并
        z = new binaryTreeNode<int> (0, x.tree, y.tree);
        w.weight = x.weight + y.weight;  //权重求和
        w.tree = z;
        heap.push(w);
    }

    //返回最后的huffman树
    return heap.top().tree;
}

#endif //DSACPP_HUFFMANTREE_H
