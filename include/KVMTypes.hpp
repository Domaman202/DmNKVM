#pragma once
#ifndef DMNKVM_KVMTYPES_HPP
#define DMNKVM_KVMTYPES_HPP

#include <KVMNM.hpp>
#include <KVMNameble.hpp>
#include <KVMLLT.hpp>

#include <cstdlib>

namespace DmN::KVM {
    /// Объект подвергающийся сборке мусора
    DMN_KVM_ES(GCObject) {
        explicit GCObject(bool isCollectable) {
            this->isCollectable = isCollectable;
            this->isCollected = false;
            this->references = 0;
        }
        /// Собран ли объект?
        bool isCollected : 1;
        /// Можно ли собирать объект?
        bool isCollectable : 1;
        /// Кол-во ссылок на объект
        uint16_t references : 10;
    };

    /// Значение
    DMN_KVM_ES(Value_t) : GCObject {
        explicit Value_t(void* value, uint8_t type, bool isCollectable) : GCObject(isCollectable) {
            this->type = type;
            this->value = value;
        }
        /// Тип значения: INT8 (1), INT16 (2), INT32 (3), INT64 (4), UINT8 (5), UINT16 (6), UINT32 (7), UINT64 (8), FLOAT (9), DOUBLE (10), CHAR (11), REFERENCE (12), OBJECT (13)
        uint8_t type : 4;
        /// Значение
        void* value;
    };

    /// Переменная
    DMN_KVM_ES(Variable_t) : LLT, Value_t, Nameble {
        Variable_t(SI_t name, void* value, uint8_t type, bool isCollectable) : LLT(0), Value_t(value, type, isCollectable), Nameble(name) { }
    };

    /// Лямбда
    DMN_KVM_ES(Lambda_t) : LLT, GCObject {
        explicit Lambda_t(SI_t descriptor, uint32_t cs, uint8_t* code) : LLT(3), GCObject(true) {
            this->descriptor = descriptor;
            this->cs = cs;
            this->code = code;
        }
        /// ID дескриптора
        SI_t descriptor;
        /// (Code Size) Размер байт-кода
        uint32_t cs;
        /// Байт-код
        uint8_t* code;
    };

    /// Поле
    DMN_KVM_ES(Field_t) : LLT, Nameble {
        explicit Field_t(SI_t name, Value_t *value) : LLT(1), Nameble(name) {
            this->value = value;
        }
        /// Значение
        Value_t* value;
    };

    /// Метод
    DMN_KVM_ES(Method_t) : LLT, Nameble, NSObject {
        explicit Method_t(SI_t descriptor, NSI_t ns, uint32_t cs, uint8_t* code) : LLT(2), Nameble(descriptor), NSObject(ns) {
            this->name = descriptor;
            this->cs = cs;
            this->code = code;
        }
        /// ID дескриптора
        SI_t name;
        /// (Code Size) Размер байт-кода
        uint32_t cs;
        /// Байт-код
        uint8_t* code;
    };
}

#endif /* DMNKVM_KVMTYPES_HPP */