cmake_minimum_required(VERSION 3.13)
project(boostpythonExamples)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(boostpythonExamples
        myfoo.so
        README.MD
        test.cpp
        test.hpp
        test.py)
