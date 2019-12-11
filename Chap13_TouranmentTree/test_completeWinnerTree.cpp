//
// Created by perry on 2019/12/11.
//

#include <iostream>
#include "completeWinnerTree.h"

using namespace std;

int main() {
    int nums[10001];
    for (int i = 1; i <= 10000; ++i)
        nums[i] = rand() % 10000;

    completeWinnerTree<int> winnerTree(nums, 10000);
    for (int i = 1; i <= 10000; ++i) {
        int winner = winnerTree.winner();
        cout << nums[winner] << endl;
        nums[winner] = INT_MAX;
        winnerTree.rePlay(winner);
    }
    return 0;
}