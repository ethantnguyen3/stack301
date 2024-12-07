cmake_minimum_required(VERSION 3.29)
project(stack301)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(stack301
    main.cpp
        evalulator.cpp
        evalulator.h
)
