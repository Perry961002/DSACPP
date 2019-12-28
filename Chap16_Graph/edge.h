//
// Created by perry on 2019/12/28.
//

#ifndef DSACPP_EDGE_H
#define DSACPP_EDGE_H

//边的抽象类edge
template <class T>
class edge {
public:
    virtual ~edge() {}

    //返回边的第一个顶点
    virtual int vertex1() const = 0;

    //返回边的第二个顶点
    virtual int vertex2() const = 0;

    //返回边的权重
    virtual int weight() const = 0;
};

#endif //DSACPP_EDGE_H
