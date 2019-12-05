cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

add_executable(Chap12_maxHeap maxPriorityQueue.h maxHeap.h ../MyExceptions.h ../Chap5_ArrayList/changeLength1D.h test_maxHeap.cpp)

add_executable(Chap12_heapSort heapSort.h test_heapSort.cpp)