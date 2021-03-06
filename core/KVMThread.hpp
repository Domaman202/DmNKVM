#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_THREAD_HPP
#define DMN_KVM_THREAD_HPP

#include "KVMCall.hpp"
#include "KVMObj.hpp"
#include "KVMSR.hpp"

namespace DmN::KVM {
    struct Thread {
        /// Стек вызовов
        Stack<Call *> *cs;
        /// Стек
        Stack<void *> *stack;
        /// Регистры
        Resisters *regs;
    };
}

#endif /* DMN_KVM_THREAD_HPP */