#include <KVMNetwork.hpp>

using namespace DmN::KVM::Network;

int main(int argc, char* argv[]) {
    NWR nwr;
    int error;
    auto server = new Server(228, nwr, error);
    auto client = new Client("localhost", false, 228, nwr, error);
    return 0;
}