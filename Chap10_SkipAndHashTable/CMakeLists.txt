cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

add_executable(Chap10_sortedChain dictionary.h sortedChain.h test_sortedchain.cpp)

add_executable(Chap10_skipList skipNode.h skipList.h dictionary.h test_skipList.cpp)

add_executable(Chap10_hashTable dictionary.h hashTable.h test_hashTable.cpp)

add_executable(Chap10_hashChain dictionary.h hashChain.h test_hashChain.cpp)