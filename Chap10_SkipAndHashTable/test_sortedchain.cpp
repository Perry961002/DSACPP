//
// Created by perry on 2019/11/18.
//

#include <iostream>
#include "sortedChain.h"

using namespace std;

int main() {
    sortedChain<char, int> s;
    for(int i = 0; i < 26; ++i) {
        s.insert(make_pair('a' + i, i));
        s.insert(make_pair('A' + i, i));
    }
    s['E']->second=8;
    cout << s.find('E')->second << endl;
    cout << s << endl;
    s.erase('E');
    cout << s << endl;
    return 0;
}