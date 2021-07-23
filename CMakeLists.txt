cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 20)

project(DmNKVM)

set(SOURCE src/DmNKVM.cpp src/DmNSTD.cpp src/Nameble.cpp)
set(HEADER include/DmNKVM.hpp include/DmNSTD.hpp)

add_executable(DmNKVM main.cpp ${HEADER} ${SOURCE})