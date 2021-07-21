cmake_minimum_required(VERSION 3.19)
project(DmNKVM)

set(CMAKE_CXX_STANDARD 20)

add_executable(DmNKVM main.cpp DmNKVM.hpp DmNKVM.cpp DmNSTD.hpp DmNSTD.cpp)