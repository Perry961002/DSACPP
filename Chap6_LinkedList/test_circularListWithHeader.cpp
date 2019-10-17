//
// Created by perry on 2019/10/17.
//

#include <iostream>
#include "circularListWithHeader.h"

using namespace std;

int main(){
    circularListWithHeader<int> numCircular;
    cout << *numCircular.begin() << endl;
    return 0;
}