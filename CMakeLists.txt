cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 20)

project(DmNKVM)

set(SOURCE src/KVMTypes.cpp src/KVMConstructors.cpp)
set(HEADER include/KVMTypes.hpp include/DmNSTD.hpp include/KVMConstructors.hpp src/KVMConstructors.cpp include/KVM.hpp include/KVMError.hpp include/KVMConfig.h)

include_directories(include)

add_executable(DmNKVM main.cpp ${HEADER} ${SOURCE})