cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

add_executable(Chap9_Queue queue.h arrayQueue.h test_Queue.cpp linkedQueue.h)

add_executable(Chap9_arrayDeque deque.h arrayDeque.h test_arrayDeque.cpp)