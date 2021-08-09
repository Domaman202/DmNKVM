cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 20)

project(DmNKVM)

set(CORE_SOURCE src/KVMConstructors.cpp src/KVMNameble.cpp src/KVMConstructors.cpp src/SDmNL.cpp)

set(CORE_HEADER include/KVMTypes.hpp include/SDmNL.hpp include/KVMConstructors.hpp include/KVMError.hpp include/KVMConfig.hpp include/KVMNameble.hpp include/KVMNM.hpp include/KVMESC.hpp include/KVMLLT.hpp include/KVMClassLoader.hpp include/KVMHeap.hpp include/KVMObj.hpp include/KVMAlloc.hpp)
set(JAVA_PARSER_HEADER include/JavaParser/KVMJPComm.h include/JavaParser/KVMJPInstruction.hpp include/JavaParser/KVMJPClass.hpp)

set(SOURCE ${CORE_SOURCE})
set(HEADER ${CORE_HEADER} ${JAVA_PARSER_HEADER})


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