cmake_minimum_required(VERSION 3.13)
project(boost_python_numpy_example)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(boost_python_numpy_example
        CMakeLists.txt
        myfoo.so
        README.MD
        test.cpp
        test.hpp
        test.py)
