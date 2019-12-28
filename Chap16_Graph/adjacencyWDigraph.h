//
// Created by perry on 2019/12/28.
//

#ifndef DSACPP_ADJACENCYWDIGRAPH_H
#define DSACPP_ADJACENCYWDIGRAPH_H

#include "graph.h"
#include "../MyExceptions.h"

//使用邻接矩阵描述的加权有向图
template <class T>
class adjacencyWDigraph : public graph<T> {
public:
    //构造和析构函数
    adjacencyWDigraph(int numberOfVertices = 0, T theNoEdge = 0);
    ~adjacencyWDigraph();

protected:
    int n;  //顶点的个数
    int e;  //边的个数
    T **a;  //邻接数组
    T noEdge;  //表示不存在的边
};

//构造函数
template <class T>
adjacencyWDigraph<T>::adjacencyWDigraph(int numberOfVertices, T theNoEdge) {
    //确定合法性
    if (numberOfVertices < 0)
        throw illegalParameterValue("number of vertices must be >= 0");

    n = numberOfVertices;
    e = 0;
    noEdge = theNoEdge;
}

#endif //DSACPP_ADJACENCYWDIGRAPH_H
