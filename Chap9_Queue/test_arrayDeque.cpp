//
// Created by perry on 2019/11/7.
//

#include <iostream>
#include "arrayDeque.h"

using namespace std;

int main() {
    arrayDeque<int> de;
    for(int i = 0; i < 25; ++i) {
        de.push_front(25 - i - 1);
        de.push_back(25 + i);
    }

    for (auto i = de.begin(); i != de.end(); ++i)
        cout << *i << " ";
    cout << endl;
    for (int i = 0; i < 5; ++i) {
        de.pop_front();
        de.pop_back();
    }

    for (auto i = de.begin(); i != de.end(); ++i)
        cout << *i << " ";
    return 0;
}