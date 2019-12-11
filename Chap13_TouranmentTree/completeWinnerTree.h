//
// Created by perry on 2019/12/10.
//

#ifndef DSACPP_COMPLETEWINNERTREE_H
#define DSACPP_COMPLETEWINNERTREE_H

#include "winnerTree.h"
#include "../MyExceptions.h"

//使用完全二叉树的数组来实现赢者树
template <class T>
class completeWinnerTree : public winnerTree<T> {
public:
    //构造和析构函数
    completeWinnerTree(T *thePlayer, int theNumberOfPlayers);
    ~completeWinnerTree() {delete[] tree;}

    //初始化一棵赢者树
    void initialize(T *thePlayer, int theNumberOfPlayers);

    //返回最终赢者的索引
    int winner() const { return tree[1];}

    //在参赛者thePLayer的分数变化之后重赛
    void rePlay(int thePLayer);

private:
    T *player;  //选手(外部结点)数组
    int *tree;  //赢者(内部结点)数组，tree[i]是player的一个索引
    int numberOfPlayers;  //选手的数量
    int lowExt;  //最底层外部结点的个数
    int offset;  //offset = 2 * s - 1，其中 s 是最底层最左端的内部结点的编号，所以offset = 2 ^ log(n - 1) - 1

    //让 theLeft 和 theRight 进行在tree[p]的比赛，并尝试在晋级之后继续比赛
    void play(int p, int theLeft, int theRight);

    //判断选手thePLayer的值改变之后，在matchNode产生的新赢者是否需要继续比赛
    bool needNext(int matchNode, int theLeft, int theRight, int thePLayer);
};

//构造函数
template <class T>
completeWinnerTree<T>::completeWinnerTree(T *thePlayer, int theNumberOfPlayers) {
    tree = NULL;
    initialize(thePlayer, theNumberOfPlayers);
}

//初始化赢者树
template <class T>
void completeWinnerTree<T>::initialize(T *thePlayer, int theNumberOfPlayers) {
    //最少要有两名选手
    if (theNumberOfPlayers < 2)
        throw illegalParameterValue("must have at least 2 players");

    //重置私有数据成员
    player = thePlayer;
    numberOfPlayers = theNumberOfPlayers;
    delete[] tree;
    tree = new int [numberOfPlayers];

    //计算最底层最左端的内部结点编号 s = 2 ^ log(n - 1)
    //s 是最接近 n-1 的2的幂
    int s = 1;
    while (s * 2 <= numberOfPlayers - 1) s *= 2;

    //lowExt = 2 * (n - s), offset = 2 * s - 1
    lowExt = 2 * (numberOfPlayers - s);
    offset = 2 * s - 1;

    //从右孩子开始，进行他所参加的比赛
    //让最底层的外部结点进行比赛
    int i;
    for (i = 2; i <= lowExt; i += 2)
        play((i + offset) / 2, i - 1, i);

    //有一个多余的外部结点需要和tree[n-1]进行比赛
    if (numberOfPlayers % 2 == 1) {
        play(numberOfPlayers / 2, tree[numberOfPlayers - 1], lowExt + 1);
        i = lowExt + 3;  //i定位到下一个需要比赛的外部结点
    }
    else
        i = lowExt + 2;  //i定位到下一个需要比赛的外部结点

    //剩余的其他选手进行比赛
    while (i <= numberOfPlayers) {
        play((i - lowExt + numberOfPlayers - 1) / 2, i - 1, i);
        i += 2;
    }
}

//让 theLeft 和 theRight 进行在tree[p]的比赛，并尝试在晋级之后继续比赛
template <class T>
void completeWinnerTree<T>::play(int p, int theLeft, int theRight) {
    //先进行theLeft和theRight的比赛
    //x <= y，当且仅当选手 x 赢了选手 y
    tree[p] = player[theLeft] <= player[theRight] ? theLeft : theRight;

    //如果p是右孩子，那么它还要进行一场比赛
    while (p % 2 == 1 && p > 1) {
        tree[p / 2] = player[tree[p-1]] <= player[tree[p]] ? tree[p-1] : tree[p];
        p /= 2;  //移动上一层
    }
}

//在参赛者thePLayer的分数变化之后重赛
template <class T>
void completeWinnerTree<T>::rePlay(int thePLayer) {
    //如果thePLayer不是正规的选手编号，则抛出异常
    if (thePLayer <= 0 || thePLayer > numberOfPlayers)
        throw illegalIndex("Player index is illegal");

    //确定thePLayer第一场比赛的对手和比赛结点
    int matchNode, theLeft, theRight;
    if (thePLayer <= lowExt) {
        //thePLayer是最底层的外部结点
        matchNode = (thePLayer + offset) / 2;
        theLeft = 2 * matchNode - offset;  //theLeft是matchNode的左孩子
        theRight = theLeft + 1;
    } else {
        //thePLayer是倒数第二层的外部结点
        matchNode = (thePLayer - lowExt + numberOfPlayers - 1) / 2;

        if (matchNode * 2 == numberOfPlayers - 1) {
            //thePLayer需要和tree[n-1]比赛
            theLeft = tree[numberOfPlayers - 1];
            theRight = thePLayer;
        } else {
            //thePLayer直接和外部结点比赛
            theLeft = matchNode * 2 - numberOfPlayers + 1 + lowExt;
            theRight = theLeft + 1;
        }
    }

    //开始重新比赛，当一场比赛的赢者和之前相同并且之前的赢者不是thePLayer时，就不用继续了
    if (!needNext(matchNode, theLeft, theRight, thePLayer))
        return;

    //如果matchNode是最后一个内部结点并且 n 是奇数，那么需要和多余的一个外部结点比赛一次
    if (matchNode == numberOfPlayers - 1 && numberOfPlayers % 2 == 1) {
        matchNode /= 2;
        if (!needNext(matchNode, tree[numberOfPlayers - 1], lowExt + 1, thePLayer))
            return;
    }

    //向上重新进行必要的比赛
    matchNode /= 2;
    while (matchNode >= 1) {
        if (!needNext(matchNode, tree[matchNode * 2], tree[matchNode * 2 + 1], thePLayer))
            break;
        matchNode /= 2;
    }
}

//判断选手thePLayer的值改变之后，在matchNode产生的新赢者是否需要继续比赛
template <class T>
bool completeWinnerTree<T>::needNext(int matchNode, int theLeft, int theRight, int thePLayer) {
    int newWinner = player[theLeft] <= player[theRight] ? theLeft : theRight;
    if (newWinner == tree[matchNode] && tree[matchNode] != thePLayer)
        return false;
    else {
        tree[matchNode] = newWinner;
        return true;
    }
}

#endif //DSACPP_COMPLETEWINNERTREE_H
