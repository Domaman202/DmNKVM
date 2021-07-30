#define USE_WIN32_EXPORT

#include <KVMConfig.hpp>

#include <cstdio>
#include <thread>

int main(int argc, char* argv[]) {
    printf("да -> %lu", sizeof(std::thread));
}