//
// Created by perry on 2019/10/31.
//

#include <iostream>
#include "spareMatrix.h"

using namespace std;

int main() {
    spareMatrix<double> m1;
    cout << "Input M: " << endl;
    cin >> m1;
    cout << m1;

    spareMatrix<double> m2;
    m1.transpose(m2);
    spareMatrix<double> w1;
    cout << "M + M^T: " << endl;
    m1.add(m2, w1);
    cout << w1;

    cout << "Input N: " << endl;
    cin >> m2;
    cout << m2;
    m1.multiply(m2, w1);
    cout << "M * N: " << endl;
    cout << w1;
    return 0;
}