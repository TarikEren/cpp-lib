cmake_minimum_required(VERSION 3.22)
project(test)

set(CMAKE_CXX_STANDARD 17)

add_executable(test main.cpp
        lib/console.h
        lib/console.cpp)
