cmake_minimum_required(VERSION 3.15)
project(LeastSquaresSmoothing)

set(CMAKE_CXX_STANDARD 14)

add_executable(LeastSquaresSmoothing src/main.cpp src/TableFun.cpp headers/TableFun.h src/System.cpp headers/System.h)