//
// Created by perry on 2019/12/5.
//

#include <iostream>
#include "heapSort.h"

using namespace std;

int main() {
    int nums[1000001];
    for (int i = 1; i <= 1000000; ++i)
        nums[i] = rand() % 1500000;
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

    heapSort(nums, 1000000);
    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<std::chrono::duration<double>>(t2 - t1)*1000;

    for (int i = 1; i < 1000000; ++i)
        if (nums[i] > nums[i+1]) {
            cout << "error" << endl;
            break;
        }

    cout << "heapSort use: " << time_used.count() << " ms" << endl;
    return 0;
}
