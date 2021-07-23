cmake_minimum_required(VERSION 3.19)
project(DmNKVM)

set(CMAKE_CXX_STANDARD 20)

add_executable(DmNKVM main.cpp include/DmNKVM.hpp src/DmNKVM.cpp include/DmNSTD.hpp src/DmNSTD.cpp)