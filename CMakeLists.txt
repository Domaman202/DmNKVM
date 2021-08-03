cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 20)

project(DmNKVM)

set(SOURCE src/KVMConstructors.cpp src/KVMNameble.cpp src/KVMConstructors.cpp src/SDmNL.cpp src/KVMJP.cpp)
set(HEADER include/KVMTypes.hpp include/SDmNL.hpp include/KVMConstructors.hpp include/KVMError.hpp include/KVMConfig.hpp include/KVMJP.hpp include/KVMNameble.hpp include/KVMNM.hpp include/KVMESC.hpp include/KVMLLT.hpp include/KVMClassLoader.hpp include/KVMHeap.hpp include/KVMObj.hpp)
include_directories(include)

if(MSVC)
    include_directories(variants/compiler/MSVC)
else()
    include_directories(variants/compiler/other)
endif()

add_executable(DmNKVM main.cpp ${HEADER} ${SOURCE})