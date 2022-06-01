cmake_minimum_required(VERSION 2.8)

project(helloThread)

add_executable(helloThread helloThread.cpp)
target_link_libraries(helloThread PUBLIC pthread) 

add_executable(testDetach testDetach.cpp)
target_link_libraries(testDetach PUBLIC pthread) 

add_executable(testProcessExit testProcessExit.cpp)
target_link_libraries(testProcessExit PUBLIC pthread) 

add_executable(testPthreadExit testPthreadExit.cpp)
target_link_libraries(testPthreadExit PUBLIC pthread) 