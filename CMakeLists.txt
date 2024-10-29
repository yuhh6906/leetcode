cmake_minimum_required(VERSION 3.22)
project(leedcode)

set(CMAKE_CXX_STANDARD 11)

add_library(leetcodelib meeting/test.cpp meeting
        /include/test.h)
add_executable(leedcode main.cpp meeting/test.cpp
        Algorithm/Huisu/Lookback.cpp
        Algorithm/Huisu/Lookback.h)

target_link_libraries(leedcode leetcodelib)