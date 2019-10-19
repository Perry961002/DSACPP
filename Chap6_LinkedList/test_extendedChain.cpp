//
// Created by perry on 2019/10/14.
//

#include "extendedChain.h"

int main(){
    extendedChain<int> numChain1, numChain2;
    for(int i = 0; i < 20; ++i){
        numChain1.push_back(i);
        numChain2.push_back(i);
    }
    numChain2.push_back(20);
    cout << "numChain1: " << numChain1 << endl << "numChain2: " << numChain2 << endl;
    numChain1.reverse();
    cout << "after numChain1.reverse(), numChain1: " << numChain1 << endl;
    numChain1.swap(numChain2);
    cout << "after numChain1.swap(numChain2), numChain1: " << numChain1 << endl;
    cout << "after numChain1.swap(numChain2), numChain2: " << numChain2 << endl;
    cout << "use iterator: ";
    for(auto it = numChain1.begin(); it != numChain1.end(); ++it)
        cout << *it << " ";
    cout << endl;
    cout << "numChain1.back(): " << numChain1.back() << endl;
    cout << "numChain1 == numChain2: " << numChain1.isEqual(numChain2) << endl;
    numChain1.push_back(55);
    cout << numChain1 << endl;
    extendedChain<int> numChain3;
    //numChain3.insert(0, 1);
    numChain3.push_front(1);
    //numChain3.erase(0);
    //numChain3.pop_front();
    cout << numChain3.back() << endl;
    numChain3.push_back(2);
    cout << numChain3 << endl;
    numChain1.removeRange(0, 4);
    cout << numChain1 << endl;


    numChain1.clear();
    
    return 0;
}
