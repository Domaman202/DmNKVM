cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 20)

project(DmNKVM)

set(SOURCE src/KVMTypes.cpp src/KVMConstructors.cpp src/KVMNameble.cpp src/KVMConstructors.cpp src/DmNSTD.cpp src/JavaParser.cpp)
set(HEADER include/KVMTypes.hpp include/DmNSTD.hpp include/KVMConstructors.hpp include/KVM.hpp include/KVMError.hpp include/KVMConfig.hpp include/JavaParser.hpp include/KVMNameble.hpp)
include_directories(include)

add_executable(DmNKVM main.cpp ${HEADER} ${SOURCE})