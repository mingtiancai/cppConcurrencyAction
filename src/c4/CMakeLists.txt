cmake_minimum_required(VERSION 2.8)

project(c4)

add_executable(testThreadSafeQueue testThreadSafeQueue.cpp)
target_link_libraries(testThreadSafeQueue PUBLIC pthread) 
