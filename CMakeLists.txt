cmake_minimum_required(VERSION 3.14)
project(DSACPP)

set(CMAKE_CXX_STANDARD 11)

add_executable(DSACPP main.cpp MyExceptions.h linearList.h changeLength1D.h arrayList.h)