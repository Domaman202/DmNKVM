#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_CALL_HPP
#define DMN_KVM_CALL_HPP

#include "KVMObj.hpp"
#include "KVMTypes.hpp"

namespace DmN::KVM::Call {
    /// Вызов функции
    struct Call {
        /// Объект который вызывал метод
        Object_t *calling_method_obj;
        /// Метод который вызывал метод
        Method_t *calling_method;
        /// Объект метод которого был вызван
        Object_t *called_method_obj;
        /// Вызываемый метод
        Method_t *called_method;
        /// Аргументы
        Value_t *args;
        /// Кол-во аргументов
        size_t args_count;
    };
}

#endif /* DMN_KVM_CALL_HPP */