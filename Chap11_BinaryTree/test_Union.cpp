//
// Created by perry on 2019/12/3.
//

#include <iostream>
#include <chrono>
#include "advancedUnion.h"

using namespace std;

int main() {
    advancedUnion test1(1000), test2(1000), test3(1000), test4(1000);

    cout << "begin test!" << endl;
    //测试不同查找算法的性能
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    for (int n = 0; n < 10000; ++n) {
        int i = test1.find(rand() % 1000 + 1);
        int j = test1.find(rand() % 1000 + 1);
        if (i != j) test1.unite(i, j);
    }
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_used = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1)*1000;
    std::cout << "find:  " << time_used.count() << " ms" << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    for (int n = 0; n < 10000; ++n) {
        int i = test2.findWithCompaction(rand() % 1000 + 1);
        int j = test2.findWithCompaction(rand() % 1000 + 1);
        if (i != j) test2.unite(i, j);
    }
    t2 = std::chrono::high_resolution_clock::now();
    time_used = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1)*1000;
    std::cout << "findWithCompaction:  " << time_used.count() << " ms" << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    for (int n = 0; n < 10000; ++n) {
        int i = test3.findWithSplitting(rand() % 1000 + 1);
        int j = test3.findWithSplitting(rand() % 1000 + 1);
        if (i != j) test3.unite(i, j);
    }
    t2 = std::chrono::high_resolution_clock::now();
    time_used = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1)*1000;
    std::cout << "findWithSplitting:  " << time_used.count() << " ms" << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    for (int n = 0; n < 10000; ++n) {
        int i = test4.findWithHalving(rand() % 1000 + 1);
        int j = test4.findWithHalving(rand() % 1000 + 1);
        if (i != j) test4.unite(i, j);
    }
    t2 = std::chrono::high_resolution_clock::now();
    time_used = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1)*1000;
    std::cout << "findWithHalving:  " << time_used.count() << " ms" << std::endl;
    return 0;
}