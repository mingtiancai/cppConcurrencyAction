cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE DEBUG)

project(cppConcurrencyAction)

add_executable(cppConcurrencyAction main.cpp)
target_link_libraries(cppConcurrencyAction PUBLIC pthread) 

add_subdirectory(src)