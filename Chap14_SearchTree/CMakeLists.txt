cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

include_directories(../Chap8_Stack)
include_directories(../Chap9_Queue)
include_directories(../Chap10_SkipAndHashTable)
include_directories(../Chap11_BinaryTree)

add_executable(Chap14_binarySearchTree ../Chap10_SkipAndHashTable/dictionary.h bsTree.h binarySearchTree.h test_binarySearchTree.cpp)

add_executable(Chap14_indexBinarySearchTree indexBSTree.h indexBinarySearchTree.h test_indexBinarySearchTree.cpp)