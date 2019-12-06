//
// Created by perry on 2019/12/6.
//

#include <iostream>
#include "maxHblt.h"

int main() {
    maxHblt<int> h;
    for (int i = 1; i <= 10000; ++i)
        h.push(rand() % 15000);

    for (int i = 1; i <= 10000; ++i) {
        cout << h.top() << endl;
        h.pop();
    }
    return 0;
}