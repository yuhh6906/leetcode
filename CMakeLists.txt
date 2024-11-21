cmake_minimum_required(VERSION 3.22)
project(leedcode)
include_directories(SYSTEM "/foo/bar")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_SYSROOT "${SYSROOT_PATH}")
set(CMAKE_FIND_ROOT_PATH "${SYSROOT_PATH}" "${CMAKE_PREFIX_PATH}" "${TOOLCHAIN_PATH}")


add_library(leetcodelib meeting/test.cpp meeting
        /include/test.h)
add_executable(leedcode main.cpp meeting/test.cpp
        Algorithm/Huisu/Lookback.cpp
        Algorithm/Huisu/Lookback.h
        Algorithm/Maths/sort.cpp
        Algorithm/sort.cpp
        main.cpp
        Algorithm/Huisu/fenzhi.cpp)

target_link_libraries(leedcode leetcodelib)