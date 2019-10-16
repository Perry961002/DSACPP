//
// Created by perry on 2019-10-10.
//

#include <iostream>
#include "chain.h"

using namespace std;

int main(){
    chain<int> numChain1, numChain2;
    for(int i = 0; i < 20; ++i){
        numChain1.insert(i, i);
        numChain2.insert(i, i);
    }
    numChain1.setSize(15);
    cout << "numChain1: " << numChain1 << endl;
    cout << "numChain1 == numChain2: " << (numChain1 == numChain2) << endl;
    cout << "numChain1.front(): " << numChain1.front() << endl;
    numChain1.front() = 1;
    cout << "after numChain1.front() = 1, numChain1: " << numChain1 << endl;
    numChain1.removeRange(11, 14);
    cout << "after numChain1.removeRange(11, 14): " << numChain1 << endl;
    numChain1.set(4, 0);
    cout << "after numChain1.set(4, 0): " << numChain1 << endl;
    cout << "numChain1: " << numChain1 << endl;
    cout << numChain1.lastIndexOf(0) << " " << numChain1.lastIndexOf(11) << endl;
    cout << "numChain1 == numChain2: " << (numChain1 == numChain2) << endl;
    cout << "numChain1 < numChain2: " << (numChain1 < numChain2) << endl;

    numChain1.swap(numChain2);
    cout << "numChain1: " << numChain1 << endl << "numChain2: " << numChain2 << endl;

    numChain1.reverse();
    cout << "numChain1.reverse(): " << numChain1 << endl;
    return 0;
}
