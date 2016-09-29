cmake_minimum_required(VERSION 3.6)
project(simple_wrapper)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    include/ns_utils.h
    include/utils.h
    src/main.cpp
    src/utils.cpp
    src/ns_utils.cpp)

include_directories(include)
include_directories(src)

add_executable(simple_wrapper ${SOURCE_FILES})
