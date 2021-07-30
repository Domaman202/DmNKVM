cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 20)

project(DmNKVM)

set(SOURCE src/KVMConstructors.cpp src/KVMNameble.cpp src/KVMConstructors.cpp src/DmNSTD.cpp src/KVMJP.cpp)
set(HEADER include/KVMTypes.hpp include/DmNSTD.hpp include/KVMConstructors.hpp include/KVM.hpp include/KVMError.hpp include/KVMConfig.hpp include/KVMJP.hpp include/KVMNameble.hpp include/KVMModule.hpp include/KVMESC.hpp include/KVMLLT.hpp include/KVMClassLoader.hpp include/KVMHeap.hpp)
include_directories(include)

add_executable(DmNKVM main.cpp ${HEADER} ${SOURCE})