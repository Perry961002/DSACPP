//
// Created by perry on 2019/10/24.
//

#include <iostream>
#include "matrix.h"

using namespace std;

int main() {
    matrix<int> m(4, 6);

    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 6; ++j) {
            m(i, j) = (rand() % 50);
        }
    }
    cout << m << endl;
    cout << m.tranpose() << endl;
    return 0;
}