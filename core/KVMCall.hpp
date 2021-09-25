#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_CALL_HPP
#define DMN_KVM_CALL_HPP

#include "KVMObj.hpp"

namespace DmN::KVM {
    /// Вызов функции
    struct Call {
        /// Объект который вызывал метод
        Object_t *obj_caller;
        /// Метод который вызывал метод
        Method_t *method_caller;
        /// Объект метод которого был вызван
        Object_t *obj;
        /// Вызываемый метод
        Method_t *method;
        /// Аргументы
        Value_t **args;
        /// Кол-во аргументов
        uint8_t argc;
    };
}

#endif /* DMN_KVM_CALL_HPP */