cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

add_executable(Chap5_arrayList test_arrayList.cpp ../MyExceptions.h linearList.h changeLength1D.h arrayList.h)

add_executable(Chap5_vectorList linearList.h vectorList.h test_vectorList.cpp ../MyExceptions.h)