#include <KVMNetwork.hpp>
#include <thread>

using namespace DmN::KVM::Network;

void check(NWR);
void networkTestS();
void networkTestC();

int main(int argc, char* argv[]) {
    return 0;
}

void networkTestS() {
    NWR nwr;
    int error;
    //
    auto server = new Server(0, nwr, error);
    //
    server->listen_(3, error);
    //
}