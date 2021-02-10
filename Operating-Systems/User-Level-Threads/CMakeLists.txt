cmake_minimum_required(VERSION 3.14.5)
project(User-Level-Threads)

set(CMAKE_CXX_STANDARD 11)

add_executable(User-Level-Threads uthreads.h uthreads.cpp Thread.h Thread.cpp)