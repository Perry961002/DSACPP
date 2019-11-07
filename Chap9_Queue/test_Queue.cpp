//
// Created by perry on 2019/11/6.
//

#include <chrono>
#include <iostream>
#include <queue>
#include "arrayQueue.h"
#include "linkedQueue.h"

using namespace std;

int main() {
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    queue<int > s1;
    for (int i = 0; i < 1000000; ++i)
        s1.push(i);
    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<std::chrono::duration<double>>(t2 - t1)*1000;
    cout << "Push 1 million integers using queue:  " << time_used.count() << " ms" << endl;

    t1 = chrono::high_resolution_clock::now();
    arrayQueue<int > s2;
    for (int i = 0; i < 1000000; ++i)
        s2.push(i);
    t2 = chrono::high_resolution_clock::now();
    time_used = chrono::duration_cast<std::chrono::duration<double>>(t2 - t1)*1000;
    cout << "Push 1 million integers using arrayQueue:  " << time_used.count() << " ms" << endl;

    t1 = chrono::high_resolution_clock::now();
    linkedQueue<int > s3;
    for (int i = 0; i < 1000000; ++i)
        s3.push(i);
    t2 = chrono::high_resolution_clock::now();
    time_used = chrono::duration_cast<std::chrono::duration<double>>(t2 - t1)*1000;
    cout << "Push 1 million integers using linkedQueue:  " << time_used.count() << " ms" << endl;

    t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i)
        s1.pop();
    t2 = chrono::high_resolution_clock::now();
    time_used = chrono::duration_cast<std::chrono::duration<double>>(t2 - t1)*1000;
    cout << "Pop 1 million integers using queue:  " << time_used.count() << " ms" << endl;

    t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i)
        s2.pop();
    t2 = chrono::high_resolution_clock::now();
    time_used = chrono::duration_cast<std::chrono::duration<double>>(t2 - t1)*1000;
    cout << "Pop 1 million integers using arrayQueue:  " << time_used.count() << " ms" << endl;

    t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i)
        s3.pop();
    t2 = chrono::high_resolution_clock::now();
    time_used = chrono::duration_cast<std::chrono::duration<double>>(t2 - t1)*1000;
    cout << "Pop 1 million integers using linkedQueue:  " << time_used.count() << " ms" << endl;
    return 0;
}