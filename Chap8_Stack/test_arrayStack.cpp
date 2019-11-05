//
// Created by perry on 2019/11/5.
//

#include <iostream>
#include <chrono>
#include <stack>
#include "arrayStack.h"

using namespace std;

int main() {
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    arrayStack<int > s1;
    for (int i = 0; i < 100000000; ++i)
        s1.push(i);
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_used = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1)*1000;
    std::cout << "Push 100 million integers using arrayStack:  " << time_used.count() << " ms" << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    stack<int > s2;
    for (int i = 0; i < 100000000; ++i)
        s2.push(i);
    t2 = std::chrono::high_resolution_clock::now();
    time_used = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1)*1000;
    std::cout << "Push 100 million integers using stack:  " << time_used.count() << " ms" << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000000; ++i)
        s1.pop();
    t2 = std::chrono::high_resolution_clock::now();
    time_used = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1)*1000;
    std::cout << "Pop 100 million integers using arrayStack:  " << time_used.count() << " ms" << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000000; ++i)
        s2.pop();
    t2 = std::chrono::high_resolution_clock::now();
    time_used = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1)*1000;
    std::cout << "Pop 100 million integers using stack:  " << time_used.count() << " ms" << std::endl;

    return 0;
}