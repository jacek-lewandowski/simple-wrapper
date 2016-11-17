cmake_minimum_required(VERSION 2.6)
project(simple_wrapper)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        include/ns_utils.h
        include/utils.h
        include/commands.h
        src/main.cpp
        src/utils.cpp
        src/ns_utils.cpp
        src/commands.cpp)

set(SAMPLE_SOURCE_FILES
        include/utils.h
        src/utils.cpp
        src/sample.cpp)

include_directories(include)
include_directories(src)

add_executable(simple_wrapper ${SOURCE_FILES})

add_executable(sample ${SAMPLE_SOURCE_FILES})
