#include <KVMNetwork.hpp>
#include <thread>
#include <iostream>

using namespace DmN::KVM::Network;

void check(NWR);
void networkTestS();
void networkTestC();

int main(int argc, char* argv[]) {
    std::thread server_thread(networkTestS);
    std::thread client_thread(networkTestC);
    server_thread.join();
    client_thread.join();
    return 0;
}

void networkTestS() {
    NWR nwr;
    int error;
    //
    auto server = new Server(228, nwr, error);
    check(nwr);
    //
    check(server->listen_(3, error));
    //
    auto connection = server->acceptConnection(nwr, error);
    check(nwr);
    //
    connection->sendBuf((void *) "Hello, World!", 13);
    //
}

void networkTestC() {
    NWR nwr;
    int error;
    //
    auto client = new Client("0.0.0.0", false, 228, nwr, error);
    check(nwr);
    //
    check(client->tryConnect(error));
    //
    char* str = new char[13];
    client->readBuf(str, 13);
    std::cout << str << std::endl;
}

inline void check(NWR nwr) {
    if (nwr != DmN::KVM::Error::SUCCESS)
        throw;
}