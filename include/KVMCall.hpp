#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_CALL_HPP
#define DMN_KVM_CALL_HPP

#include "KVMConfig.hpp"
#include "KVMTypes.hpp"

namespace DmN::KVM {
    DMN_KVM_E struct Call {
        /// Метод который вызывал код
        Method_t* calling_method;
        /// Вызываемый метод
        Method_t* called_method;
        /// Аргументы
        Value_t* args;
        /// Кол-во аргументов
        size_t args_count;
    };
}

#endif /* DMN_KVM_CALL_HPP */