//
// Created by perry on 2019/12/28.
//

#ifndef DSACPP_VERTEXITERATOR_H
#define DSACPP_VERTEXITERATOR_H

//顶点访问迭代器的抽象类vertexIterator
template <class T>
class vertexIterator {
public:
    virtual ~vertexIterator() {}

    //返回与当前顶点相邻的一个顶点
    virtual int next() = 0;

    //返回与当前顶点相邻的一个顶点，并设置为指定权重
    virtual int next(T&) = 0;
};

#endif //DSACPP_VERTEXITERATOR_H
