//
// Created by perry on 2019/12/13.
//

#include <iostream>
#include "indexBinarySearchTree.h"

using namespace std;

int main() {
    indexBinarySearchTree<int, int> indexTree;
    for (int i = 0; i < 20; ++i) {
        int num = rand() % 30;
        indexTree.insert({num, 1});
        cout << num << " ";
    }
    cout << endl;
    indexTree.erase(19);
    indexTree.erase(23);
    indexTree.erase(7);
    indexTree.eraseIndex(5);
    indexTree.ascend();
    return 0;
}