#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_PROCESS_H
#define DMN_KVM_PROCESS_H

#include "KVMConfig.hpp"
#include "KVMHeap.hpp"

namespace DmN::KVM {
    DMN_KVM_E struct Process {
        Heap* heap = nullptr;
    };
}

#endif /* DMN_KVM_PROCESS_H */