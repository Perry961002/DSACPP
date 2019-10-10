cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 11)

add_executable(arrayList test_arrayList.cpp MyExceptions.h linearList.h changeLength1D.h arrayList.h)

add_executable(vectorList linearList.h vectorList.h test_vectorList.cpp MyExceptions.h)