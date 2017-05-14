cmake_minimum_required(VERSION 3.5)
project(ZZBrain)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp lib/matrix.cpp lib/misc.cpp lib/matrix.h lib/misc.h lib/ZZNetwork.cpp lib/ZZNetwork.h test/test.cpp test/test.h)
add_executable(ZZBrain ${SOURCE_FILES})