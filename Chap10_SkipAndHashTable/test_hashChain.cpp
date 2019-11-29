//
// Created by perry on 2019/11/29.
//

#include <iostream>
#include "hashChain.h"

using namespace std;

int main() {
    hashChain<int, int> z(11);
    pair<int, int> p;

    // test insert
    p.first = 0; p.second = 3;
    z.insert(p);
    p.first = 2; p.second = 10;
    z.insert(p);
    p.first = 10; p.second = 50;
    z.insert(p);
    p.first = 24; p.second = 120;
    z.insert(p);
    p.first = 32; p.second = 160;
    z.insert(p);
    p.first = 3; p.second = 15;
    z.insert(p);
    p.first = 12; p.second = 60;
    z.insert(p);
    p.first = 21; p.second = 8;
    z.insert(p);
    cout << "The dictionary is " << endl << z << endl;
    cout << "Its size is " << z.size() << endl;

    // test find
    cout << "Element associated with 2 is " << z.find(2)->second << endl;
    cout << "Element associated with 10 is " << z.find(10)->second << endl;
    cout << "Element associated with 12 is " << z.find(12)->second << endl;

    // test erase
    z.erase(10);
    cout << "Delete the element whose key is 10: " << z << endl;
    z.erase(2);
    cout << "Delete the element whose key is 2: " << z << endl;

    p.first = 21; p.second = 4;
    z.insert(p);
    p.first = 43; p.second = 89;
    z.insert(p);
    p.first = 54; p.second = 78;
    z.insert(p);
    cout << "Insert the elements(<21, 4>, <43, 89>, <54, 78>): " << z << endl;
    return 0;
}
