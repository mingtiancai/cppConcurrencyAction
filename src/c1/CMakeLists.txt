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

add_executable(testException testException.cpp)
target_link_libraries(testException PUBLIC pthread) 

add_executable(testThreadGuardException testThreadGuardException.cpp)
target_link_libraries(testThreadGuardException PUBLIC pthread) 

add_executable(testRef testRef.cpp)
target_link_libraries(testRef PUBLIC pthread)

add_executable(testUseMove testUseMove.cpp)
target_link_libraries(testUseMove PUBLIC pthread)

add_executable(testMoveOwner testMoveOwner.cpp)
target_link_libraries(testMoveOwner PUBLIC pthread)

add_executable(testScopeThread testScopeThread.cpp)
target_link_libraries(testScopeThread PUBLIC pthread)