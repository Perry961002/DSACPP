//
// Created by perry on 2019/12/12.
//

#include <iostream>
#include "skipList.h"
#include "binarySearchTree.h"

using namespace std;

int main() {
    //做一个跳表和二叉搜索树的性能测试
    int keys[10000];  //保存关键字的数组
    skipList<int, int> skip(20000);
    binarySearchTree<int, int> bsTree;
    for (int i = 0; i < 10000; ++i) {
        int key = rand() % 20000;
        keys[i] = key;
    }

    chrono::high_resolution_clock::time_point t1, t2;
    chrono::duration<double> time_used;
    //开始插入测试
    t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) {
        skip.insert(make_pair(keys[i], 1));
    }
    t2 = chrono::high_resolution_clock::now();
    time_used = chrono::duration_cast<std::chrono::duration<double>>(t2 - t1)*1000;
    cout << "Insert 10000 keywords into skip: " << time_used.count() << " ms" << endl;
    cout << "skip.size(): " << skip.size() << endl;

    t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) {
        bsTree.insert(make_pair(keys[i], 1));
    }
    t2 = chrono::high_resolution_clock::now();
    time_used = chrono::duration_cast<std::chrono::duration<double>>(t2 - t1)*1000;
    cout << "Insert 10000 keywords into bsTree: " << time_used.count() << " ms" << endl;
    cout << "bsTree.size(): " << bsTree.size() << endl << "bsTree.height(): " << bsTree.height() << endl << endl;

    //开始测试查找的性能
    t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) {
        skip.find(keys[i]);
    }
    t2 = chrono::high_resolution_clock::now();
    time_used = chrono::duration_cast<std::chrono::duration<double>>(t2 - t1)*1000;
    cout << "find 10000 keywords into skip: " << time_used.count() << " ms" << endl;

    t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) {
        bsTree.find(keys[i]);
    }
    t2 = chrono::high_resolution_clock::now();
    time_used = chrono::duration_cast<std::chrono::duration<double>>(t2 - t1)*1000;
    cout << "find 10000 keywords into bsTree: " << time_used.count() << " ms" << endl << endl;

    //开始测试删除的性能
    t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) {
        skip.erase(keys[i]);
    }
    t2 = chrono::high_resolution_clock::now();
    time_used = chrono::duration_cast<std::chrono::duration<double>>(t2 - t1)*1000;
    cout << "erase 10000 keywords into skip: " << time_used.count() << " ms" << endl;

    t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) {
        bsTree.erase(keys[i]);
    }
    t2 = chrono::high_resolution_clock::now();
    time_used = chrono::duration_cast<std::chrono::duration<double>>(t2 - t1)*1000;
    cout << "erase 10000 keywords into bsTree: " << time_used.count() << " ms" << endl;

    return 0;
}