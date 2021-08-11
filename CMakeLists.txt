cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 20)

project(DmNKVM)

file(GLOB_RECURSE SOURCE "*.cpp")
file(GLOB_RECURSE HEADER "*.hpp")

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