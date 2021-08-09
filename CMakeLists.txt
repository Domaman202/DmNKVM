cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 20)

project(DmNKVM)

set(SOURCE src/KVMConstructors.cpp src/KVMNameble.cpp src/KVMConstructors.cpp src/SDmNL.cpp src/KVMJP.cpp)
set(HEADER include/KVMTypes.hpp include/SDmNL.hpp include/KVMConstructors.hpp include/KVMError.hpp include/KVMConfig.hpp include/KVMJP.hpp include/KVMNameble.hpp include/KVMNM.hpp include/KVMESC.hpp include/KVMLLT.hpp include/KVMClassLoader.hpp include/KVMHeap.hpp include/KVMObj.hpp include/KVMAlloc.hpp)
include_directories(include)

if(MSVC)
    include_directories(variants/compiler/MSVC)
else()
    include_directories(variants/compiler/other)
endif()

add_library(DmNKVMSt STATIC ${HEADER} ${SOURCE})
add_library(DmNKVMSh SHARED ${HEADER} ${SOURCE})
add_library(DmNKVMMo MODULE ${HEADER} ${SOURCE})
add_executable(DmNKVMExe main.cpp ${HEADER} ${SOURCE})