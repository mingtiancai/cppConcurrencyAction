cmake_minimum_required(VERSION 2.8)

project(c3)

add_executable(testLock testLock.cpp)
target_link_libraries(testLock PUBLIC pthread) 

add_executable(testCallOnce testCallOnce.cpp)
target_link_libraries(testCallOnce PUBLIC pthread) 

add_executable(testSharedMutex testSharedMutex.cpp)
target_link_libraries(testSharedMutex PUBLIC pthread) 