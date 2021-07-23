cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 20)

project(DmNKVM)

set(SOURCE src/DmNKVM.cpp)
set(HEADER include/DmNKVM.hpp include/DmNSTD.hpp)

include_directories(include)

add_executable(DmNKVM main.cpp ${HEADER} ${SOURCE})