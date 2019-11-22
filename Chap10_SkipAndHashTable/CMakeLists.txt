cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

add_executable(Chap10_sortedChain dictionary.h sortedChain.h test_sortedchain.cpp)

#因为数对的Key是const的，所以在插入新数对时比较麻烦，就不写了

add_executable(Chap10_skipList skipNode.h skipList.h dictionary.h test_skipList.cpp)