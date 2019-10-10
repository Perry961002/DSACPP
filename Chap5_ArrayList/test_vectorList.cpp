//
// Created by perry on 2019-10-09.
//

#include <iostream>
#include "vectorList.h"

int main(){
    vectorList<int> nums1;
    for(int i = 0; i < 31; ++i)
        nums1.push_back(i);
    cout << nums1.get(20) << endl;
    nums1[30] = 0;
    cout << nums1 << endl;
    nums1.pop_back();
    for(auto it = nums1.begin(); it < nums1.end(); ++it){
        cout << *it << " ";
    }
    vectorList<int> nums2;
    nums2.push_back(1);
    nums1.swap(nums2);
    cout << nums1 << endl << nums2 << endl;
    return 0;
}