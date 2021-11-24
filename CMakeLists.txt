cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_CXX_STANDARD 20)

project(DmNKVM)

file(GLOB_RECURSE HEADER core/*.hpp)

include_directories(./)

if(MSVC)
    include_directories(variants/compiler/MSVC)
elseif(CYGWIN)
    include_directories(variants/compiler/Cygwin)
elseif(MINGW)
    if (WIN32)
        link_libraries(wsock32 ws2_32)
    endif()
    include_directories(variants/compiler/MinGW)
else()
    include_directories(variants/compiler/other)
endif()

add_library(DmNKVMSt STATIC ${HEADER})
set_target_properties(DmNKVMSt PROPERTIES LINKER_LANGUAGE CXX)

add_library(DmNKVMSh SHARED ${HEADER})
set_target_properties(DmNKVMSh PROPERTIES LINKER_LANGUAGE CXX)

add_library(DmNKVMMo MODULE ${HEADER})
set_target_properties(DmNKVMMo PROPERTIES LINKER_LANGUAGE CXX)

add_executable(DmNKVMExe main.cpp ${HEADER})
target_link_libraries(DmNKVMExe PUBLIC pthread)