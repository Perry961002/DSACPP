//
// Created by perry on 2019/12/9.
//

#include <iostream>
#include "maxWblt.h"

int main() {
    maxWblt<int> h;
    int nums[10001];
    for (int i = 1; i <= 10000; ++i)
        nums[i] = rand() % 15000;
    h.initialize(nums, 10000);
    for (int i = 1; i <= 10000; ++i) {
        cout << h.top() << endl;
        h.pop();
    }
    return 0;
}