cmake_minimum_required(VERSION 2.8)

project(c3)

add_executable(testLock testLock.cpp)
target_link_libraries(testLock PUBLIC pthread) 