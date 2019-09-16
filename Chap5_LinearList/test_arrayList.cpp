#include <iostream>
#include "arrayList.h"
int main() {
    arrayList<int> nums1(10);
    arrayList<int> nums2(15);
    for(int i = 0; i < 10; ++i) {
        nums1.insert(i, i + 1);
        nums2.insert(i, i + 1);
    }
    cout << nums1.get(3) << endl;
    cout << nums1 << endl;
    //nums1[5] = 0;
    cout << nums1[5] << endl;
    cout << (nums1 == nums2) << endl;
    cout << (nums1 != nums2) << endl;
    cout << (nums1 < nums2) << endl;
    nums1.pop_back();
    cout << nums1 << endl;
    cout << (nums1 != nums2) << endl;
    nums1.push_back(11);
    cout << nums1 << endl;
    cout << (nums1 > nums2) << endl;

    nums1.setSize(20);
    cout << "size:" << nums1.size() << endl;
    nums1.set(6, 8);
    cout << nums1 << endl;

    nums1.removeRange(2, 5);
    cout << nums1 << endl;

    nums2.reverse();
    cout << nums2 << endl;

    nums1.swap(nums2);
    cout << nums1 << endl << nums2 << endl;

    nums2.clear();

    return 0;
}