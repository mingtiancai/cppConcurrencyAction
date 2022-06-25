cmake_minimum_required(VERSION 2.8)

project(c4)

add_executable(testThreadSafeQueue testThreadSafeQueue.cpp)
target_link_libraries(testThreadSafeQueue PUBLIC pthread)

add_executable(testFuture testFuture.cpp)
target_link_libraries(testFuture PUBLIC pthread)

add_executable(testPackagedTasks testPackagedTasks.cpp)
target_link_libraries(testPackagedTasks PUBLIC pthread)

add_executable(testPromise testPromise.cpp)
target_link_libraries(testPromise PUBLIC pthread)
