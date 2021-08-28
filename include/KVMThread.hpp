#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_THREAD_HPP
#define DMN_KVM_THREAD_HPP

#include "KVMConfig.hpp"
#include "KVMSR.hpp"

namespace DmN::KVM {
    DMN_KVM_E struct Thread {
        Stack* stack;
        Resisters* regs;
    };
}

#endif /* DMN_KVM_THREAD_HPP */