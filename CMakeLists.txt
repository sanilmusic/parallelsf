cmake_minimum_required(VERSION 3.9)
project(ParallelSF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

add_executable(ParallelSF main.cpp ParallelSF.cpp ParallelSF.h Node.cpp Node.h)