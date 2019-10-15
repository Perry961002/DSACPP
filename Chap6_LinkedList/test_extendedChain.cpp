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
    cout << "numChain1: " << numChain1 << endl;
    cout << "use iterator: ";
    for(auto it = numChain1.begin(); it != numChain1.end(); ++it)
        cout << *it << " ";
    cout << endl;

    cout << "numChain1 == numChain2: " << numChain1.isEqual(numChain2) << endl;

    return 0;
}
