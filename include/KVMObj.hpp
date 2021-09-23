#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_OBJ_HPP
#define DMN_KVM_OBJ_HPP

#include "KVMESC.hpp"

namespace DmN::KVM {
    /// Объект (нет) который может быть инстансирован
    struct Instanceble_t {
        virtual struct Object_t *newInstance(Value_t** args, size_t args_c) = 0;
    };

    /// Объект
    struct Object_t {
        /// Тип объекта
        Instanceble_t *type;
    };

    /// Динамический объект
    class DynamicObject_t : public Object_t {
    public:
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
