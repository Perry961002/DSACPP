//
// Created by perry on 2019/12/13.
//

#include <iostream>
#include "indexBinarySearchTree.h"

using namespace std;

int main() {
    indexBinarySearchTree<int, int> indexTree;
    for (int i = 0; i < 15; ++i) {
        int num = rand() % 15;
        indexTree.insert({num, 1});
        cout << num << " ";
    }
    cout << endl;
    indexTree.ascend();
    return 0;
}