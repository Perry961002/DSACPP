//
// Created by perry on 2019/10/17.
//

#include <iostream>
#include "circularListWithHeader.h"

using namespace std;

int main(){
    circularListWithHeader<int> numCircular1, numCircular2;
    for(int i = 0; i < 21; ++i) {
        numCircular1.push_back(i);
        numCircular2.push_front(i);
    }
    cout << "numCircular1: " << numCircular1 << endl;
    cout << "numCircular2: " << numCircular2 << endl;
    cout << "numCircular1 == numCircular2: " << (numCircular1 == numCircular2) << endl;
    numCircular2.reverse();
    cout << "after numCircular2.reverse(): " << numCircular2 << endl;
    cout << "numCircular2 use iterator: ";
    for(auto it = numCircular2.begin(); it != numCircular2.end(); ++it)
        cout << *it << " ";
    cout << endl;
    cout << "numCircular1 == numCircular2: " << (numCircular1 == numCircular2) << endl;
    numCircular1.insert(5, 0);
    cout << "after numCircular1.insert(5, 7): " << numCircular1 << endl;
    numCircular2.pop_front();
    cout << "after numCircular2.pop_back(): " << numCircular2 << endl;
    numCircular1.erase(0);
    cout << "after numCircular1.erase(0): " << numCircular1 << endl;
    cout << "numCircular1 < numCircular2: " << (numCircular1 < numCircular2) << endl;
    numCircular2.setSize(10);
    cout << "after numCircular2.setSize(10): " << numCircular2 << endl;
    numCircular1.set(4, 5);
    cout << "after numCircular1.set(4, 5): " << numCircular1 << endl;
    numCircular1.removeRange(5, 20);
    cout << "after numCircular1.removeRange(5, 20): " << numCircular1 << endl;
    numCircular1.swap(numCircular2);
    cout << "after numCircular1.swap(numCircular2), numCircular1: " << numCircular1 << endl;
    cout << "after numCircular1.swap(numCircular2), numCircular2: " << numCircular2 << endl;
    numCircular1.push_back(55);
    numCircular2.push_back(66);
    cout << "after numCircular1.swap(numCircular2), numCircular1: " << numCircular1 << endl;
    cout << "after numCircular1.swap(numCircular2), numCircular2: " << numCircular2 << endl;
    cout << numCircular1.size() << " " << numCircular2.size() << endl;
    numCircular1.clear();
    numCircular2.clear();
    return 0;
}