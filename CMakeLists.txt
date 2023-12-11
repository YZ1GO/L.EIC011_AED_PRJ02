cmake_minimum_required(VERSION 3.27)
project(aed_aeroporto)

set(CMAKE_CXX_STANDARD 17)

add_library(untitled STATIC library.cpp
        ReadData.h
        Data.cpp)
