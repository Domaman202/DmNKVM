#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMNKVM_THROWABLE_HPP
#define DMNKVM_THROWABLE_HPP

#include "KVMConfig.hpp"
#inlucde "KVMThread.hpp"

namespace DmN::KVM {
    DMN_KVM_E struct Throwable {
        /// Поток из которого было выброшено исключение
        Thread* thread;
        /// Сообщение об ошибке
        char* message;
    };
}

#endif /* DMNKVM_THROWABLE_HPP */