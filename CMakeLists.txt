cmake_minimum_required(VERSION 2.8)

project("Unix Info")

enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall")

add_executable(SharedObjectTest  ../tests/SharedObjectTest.cpp ../src/Process.cpp)

add_test(SharedObjectTest SharedObjectTest)

add_executable(uxInfo main.cpp src/DirectoryInfo.cpp src/Information.cpp src/Module.cpp src/Process.cpp)