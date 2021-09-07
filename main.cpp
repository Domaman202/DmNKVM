#include <KVMNetwork.hpp>
#include <thread>
#include <iostream>
#include <cstring>

#define NO_THROW

using namespace DmN::KVM::Network;

uint16_t __PORT__;

void check(NWR);
void networkTestS();
void networkTestC();

int main(int argc, char* argv[]) {
    __PORT__ = 228;
    std::thread server_thread(networkTestS);
    std::thread client_thread(networkTestC);
    client_thread.join();
    server_thread.join();

    return 0;
}

void networkTestS() {
    NWR nwr;
    int error;
    //
    auto server = new Server(__PORT__, nwr, error);
    check(nwr);
    //
    check(server->listen_(1, error));
    //
    auto connection = server->accept(nwr, error);
    check(nwr);
    //
    auto chars = new char[1024];
    memcpy(chars, "Hello, World!", 13);
    connection->sendBuf(chars, 1024);
    //
    connection->close();
    server->close();
}

void networkTestC() {
    NWR nwr;
    int error;
    //
    auto client = new Client("0.0.0.0", false, __PORT__, nwr, error);
    check(nwr);
    //
    check(client->tryConnect(error));
    //
    char* str = new char[1024];
    client->readBuf(str, 1024);
    std::cout << str << std::endl;
    delete[] str;
    //
    client->close();
}

inline void check(NWR nwr) {
#ifndef NO_THROW
    if (nwr != DmN::KVM::Error::SUCCESS)
        throw;
#endif /* NO_THROW */
}