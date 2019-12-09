cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

include_directories(../Chap11_BinaryTree)
include_directories(../Chap8_Stack)
include_directories(../Chap9_Queue)

add_executable(Chap12_maxHeap maxPriorityQueue.h maxHeap.h ../MyExceptions.h ../Chap5_ArrayList/changeLength1D.h test_maxHeap.cpp)

add_executable(Chap12_heapSort heapSort.h test_heapSort.cpp)

add_executable(Chap12_maxHblt ../Chap11_BinaryTree/binaryTree.h maxHblt.h maxPriorityQueue.h test_maxHblt.cpp)

add_executable(Chap12_maxWblt ../Chap11_BinaryTree/binaryTree.h maxPriorityQueue.h maxWblt.h test_maxWblt.cpp)

add_executable(Chap12_huffmanTree minHeap.h huffmanTree.h)