cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 11)

include_directories(../Chap5_ArrayList)

add_executable(Chap6_chain chainNode.h chain.h test_chain.cpp)

add_executable(Chap6_extendedChain extendedLinearList.h extendedChain.h test_extendedChain.cpp)