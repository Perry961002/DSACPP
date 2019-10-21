//
// Created by perry on 2019/10/20.
//

#include <iostream>
#include "doublyLinkedListWithHeader.h"

using namespace std;

int main(){
    doublyLinkedListWithHeader<int> nums1, nums2;
    for(int i = 0; i < 30; ++i) {
        nums1.push_back(i);
        nums2.push_front(i);
    }
    cout << "nums1: " << nums1 << endl << "nums2: " << nums2 << endl;
    nums1.pop_front();
    nums1.pop_back();
    cout << "after nums1.pop_front(), nums1.pop_back(): " << nums1 << endl;
    cout << "for(auto it = ++nums2.end(); it != nums2.end(); ++it): ";
    for(auto it = ++nums2.end(); it != nums2.end(); ++it)
        cout << *it << " ";
    cout << endl;
    nums1.swap(nums2);
    cout << "after nums1.swap(nums2):" << endl;
    cout << "nums1: " << nums1 << endl << "nums2: " << nums2 << endl;
    nums1.reverse();
    cout << "after nums1.reverse(): " << nums1 << endl;
    nums1.removeRange(3, 10);
    nums1.set(3, 3);
    nums1.insert(4, 4);
    cout << "nums1.removeRange(3, 10), nums1.set(3, 3), nums1.insert(4, 4): " << nums1 << endl;
    nums1.erase(5);
    cout << "after nums1.erase(5): " << nums1 << endl;
    return 0;
}