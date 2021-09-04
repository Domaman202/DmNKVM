cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 20)

project(DmNKVM)

file(GLOB_RECURSE SOURCE ./src/*.cpp)
file(GLOB_RECURSE HEADER ./include/*.hpp)

include_directories(include)

if(MSVC)
    include_directories(variants/compiler/MSVC)
else()
    include_directories(variants/compiler/other)
endif()

add_library(DmNKVMSt STATIC ${HEADER} ${SOURCE} ${TEMPLATE_SOURCE})
add_library(DmNKVMSh SHARED ${HEADER} ${SOURCE} ${TEMPLATE_SOURCE})
add_library(DmNKVMMo MODULE ${HEADER} ${SOURCE} ${TEMPLATE_SOURCE})
add_executable(DmNKVMExe main.cpp ${HEADER} ${SOURCE} ${TEMPLATE_SOURCE})