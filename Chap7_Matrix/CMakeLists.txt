cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 11)

include_directories(../Chap5_ArrayList)

add_executable(Chap7_matrix matrix.h test_matrix.cpp)

add_executable(Chap7_spareMatrix spareMatrix.h test_spareMatrix.cpp)