#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMNKVM_THROWABLE_HPP
#define DMNKVM_THROWABLE_HPP

#include "KVMNameble.hpp"
#include "KVMThread.hpp"

namespace DmN::KVM {
    struct Throwable : Nameble {
        Throwable(Thread *thread, SI_t error) : Nameble(error) {
            this->thread = thread;
        }

        /// Поток из которого было выброшено исключение
        Thread *thread = nullptr;
    };
}

#endif /* DMNKVM_THROWABLE_HPP */