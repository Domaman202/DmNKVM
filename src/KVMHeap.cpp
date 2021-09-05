#include <KVMHeap.hpp>

namespace DmN::KVM {
    void Heap::operator+(const Heap *heap, SS* last_heap_strings,  const SS* strings) {
        auto map = last_heap_strings->add(strings);

    }
}