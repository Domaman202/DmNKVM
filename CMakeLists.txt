cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 20)

project(DmNKVM)

set(SOURCE src/KVMTypes.cpp)
set(HEADER include/KVMTypes.hpp include/DmNSTD.hpp include/constructors.hpp)

include_directories(include)

add_executable(DmNKVM main.cpp ${HEADER} ${SOURCE})