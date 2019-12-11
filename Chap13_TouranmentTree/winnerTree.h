//
// Created by perry on 2019/12/10.
//

#ifndef DSACPP_WINNERTREE_H
#define DSACPP_WINNERTREE_H

//赢者树的抽象类
template <class T>
class winnerTree {
public:
    virtual ~winnerTree() {}

    //用数组thePlayer[1:numberOfPlayers]生成赢者树
    virtual void initialize(T *thePlayer, int theNumberOfPlayers) = 0;

    //返回最终赢者的索引
    virtual int winner() const = 0;

    //在参赛者thePLayer的分数变化之后重赛
    virtual void rePlay(int thePLayer) = 0;
};


#endif //DSACPP_WINNERTREE_H
