#include <iostream>
#include "arrayList.h"
int main() {
    arrayList<int> nums(10);
    for(int i = 0; i < 10; ++i)
        nums.insert(i, i + 1);
    cout << nums.get(3) << endl;
    cout << nums << endl;
    return 0;
}