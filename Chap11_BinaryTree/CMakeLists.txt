cmake_minimum_required(VERSION 3.10)
project(DSACPP)

set(CMAKE_CXX_STANDARD 11)

include_directories(../Chap8_Stack)
include_directories(../Chap9_Queue)

add_executable(Chap11_linkedBinaryTree binaryTree.h binaryTreeNode.h linkedBinaryTree.h test_binaryTree.cpp)