#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_OBJ_HPP
#define DMN_KVM_OBJ_HPP

#include "KVMESC.hpp"

namespace DmN::KVM {
    DMN_KVM_E struct Instanceble_t {
        virtual struct Object_t *newInstance(Value_t** args, size_t args_c) = 0;
    };

    DMN_KVM_E struct Object_t
        /// Тип объекта
        Instanceble *type;
    };

    DMN_KVM_E struct DynamicObject_t : Object_t {
        /// Методы объекта
        Method_t **methods;
        /// Кол-во методов
        uint8_t methods_count;
        /// Поля объекта
        Field_t **fields;
        /// Кол-во полей
        uint8_t fields_count;
    };
}

#endif /* DMN_KVM_OBJ_HPP */
