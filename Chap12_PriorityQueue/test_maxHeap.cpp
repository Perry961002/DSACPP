//
// Created by perry on 2019/12/4.
//

#include <iostream>
#include "maxHeap.h"

using namespace std;

int main() {
    maxHeap<int> h;
    for (int i = 1; i <= 100000; ++i)
        h.push(rand() % 150000);

    for (int i = 1; i <= 100000; ++i) {
        cout << h.top() << endl;
        h.pop();
    }
    return 0;
}