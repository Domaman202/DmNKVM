#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_VM_HPP
#define DMN_KVM_VM_HPP

#include "KVMThread.hpp"
#include "KVMCall.hpp"
#include "KVMESC.hpp"

namespace DmN::KVM::VM {
    /// Контекст выполнения
    struct ExecuteContext {
        /// Текущий вызов
        Call::Call* lastCall;
        /// Текущий поток
        Thread* lastThread;
        /// Текущий указатель кода
        uint64_t lastBcPtr;
        /// Предыдущий вызов
        ExecuteContext* prevContext;
    };

    /// Виртуальная машина A класса
    class VMCA {
    public:
        ExecuteContext* mainContext;
        BCMethod_t* main;

        VMCA(uint8_t* code, size_t cs) {
            main = createMain(code, cs);
        }
    };

    BCMethod_t* createMain(uint8_t* code, size_t cs) {
        return new BCMethod_t("$main()V")
    }
}

#endif /* DMN_KVM_VM_HPP */