cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

add_executable(Chap8_arrayStack arrayStack.h stack.h test_arrayStack.cpp)

add_executable(Chap8_linkedStack linkedStack.h test_linkedStack.cpp)