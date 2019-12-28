//
// Created by perry on 2019/12/28.
//

#ifndef DSACPP_GRAPH_H
#define DSACPP_GRAPH_H

#include "edge.h"
#include "vertexIterator.h"

//图的抽象类graph
template <class T>
class graph {
public:
    virtual ~graph() {}

    //返回图的顶点数
    virtual int numberOfVertices() const = 0;

    //返回图的边数
    virtual int numberOfEdges() const = 0;

    //判断边是否存在
    virtual bool existsEdge(int, int) const = 0;

    //插入边
    virtual void insertEdge(edge<T>*) = 0;

    //删除边
    virtual void eraseEdge(int, int) = 0;

    //返回顶点的度
    virtual int degree(int) const = 0;

    //返回顶点的入度
    virtual int inDegree(int) const = 0;

    //返回顶点的出度
    virtual int outDegree(int) const = 0;


    //当且仅当是有向图的时候返回true
    virtual bool directed() const = 0;

    //当且仅当是无向图的时候返回true
    virtual bool weighted() const = 0;

    //访问指定顶点的相邻结点
    virtual vertexIterator<T>* iterator(int) = 0;
};

#endif //DSACPP_GRAPH_H
