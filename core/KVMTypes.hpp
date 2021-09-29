#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_TYPES_HPP
#define DMN_KVM_TYPES_HPP

#include "KVMESC.hpp"
#include "KVMLLT.hpp"
#include "KVMNM.hpp"
#include <cstdlib>

namespace DmN::KVM {
    /// Объект подвергающийся сборке мусора
    struct GCObject {
        explicit GCObject(bool isCollectable) {
            this->isCollectable = isCollectable;
            this->references = 0;
        }

        /// Можно ли собирать объект?
        bool isCollectable: 1;
        /// Кол-во ссылок на объект
        uint16_t references: 10;
    };

    enum class VTypes {
        UNDEFINED = 0,
        NaN = 1,
        INF = 2,
        INT8 = 3,
        INT16 = 4,
        INT32 = 5,
        INT64 = 6,
        UINT8 = 7,
        UINT16 = 8,
        UINT32 = 9,
        UINT64 = 10,
        FLOAT = 11,
        DOUBLE = 12,
        CHAR = 13,
        REFERENCE = 14,
        OBJECT = 15
    };

    /// Значение
    struct Value_t : public GCObject, public LLT {
        explicit Value_t(void *value, uint8_t type, bool isCollectable) : GCObject(isCollectable), LLT(LLTypes::VARIABLE) {
            this->type = type;
            this->value = value;
        }

        /// Тип значения: UNDEFINED (0), NaN (1), INF (2), INT8 (3), INT16 (4), INT32 (5), INT64 (6), UINT8 (7), UINT16 (8), UINT32 (9), UINT64 (10), FLOAT (11), DOUBLE (12), CHAR (13), REFERENCE (14), OBJECT (15)
        uint8_t type: 4;
        /// Значение
        void *value;
    };

    /// Переменная
    struct Variable_t : public LLTNameble, public Value_t {
        Variable_t(SI_t name, void *value, uint8_t type, bool isCollectable) : LLTNameble(name, LLTypes::VARIABLE),
                                                                               Value_t(value, type, isCollectable) {}
    };

    /// Лямбда
    class Lambda_t : public LLT, public GCObject {
        explicit Lambda_t(SI_t descriptor, uint32_t cs, uint8_t *code) : LLT(LLTypes::LAMBDA), GCObject(true) {
            this->descriptor = descriptor;
            this->cs = cs;
            this->code = code;
        }

        /// ID дескриптора
        SI_t descriptor;
        /// (Code Size) Размер байт-кода
        uint32_t cs;
        /// Байт-код
        uint8_t *code;
    };

    /// Поле
    class Field_t : public LLT, public Nameble {
    public:
        explicit Field_t(SI_t name, Value_t *value) : LLT(LLTypes::FIELD), Nameble(name) {
            this->value = value;
        }

        /// Значение
        Value_t *value;
    };

    /// Метод
    class Method_t : public LLT, public Nameble {
    public:
        explicit Method_t(SI_t descriptor) : LLT(LLTypes::METHOD), Nameble(descriptor) {
            this->name = descriptor;
        }

        /// ID дескриптора
        SI_t name;
    };

    class BCMethod_t : public Method_t {
    public:
        BCMethod_t(SI_t descriptor, uint8_t* bc, size_t cs) : Method_t(descriptor) {
            this->bc = bc;
            this->cs = cs;
        }

        uint8_t* bc;
        size_t cs;
    };

    class NMethod_t : public Method_t {
    public:
        explicit NMethod_t(SI_t descriptor) : Method_t(descriptor) {}

        virtual void* call(void **args, size_t argc) = 0;
    };

    typedef void *(KVMMethod)(void **args, size_t argc);

    class NRMethod_t : public Method_t {
    public:
        NRMethod_t(KVMMethod *method, SI_t descriptor) : Method_t(descriptor) {
            this->ref = method;
        }

        KVMMethod *ref;
    };
}

#endif /* DMN_KVM_TYPES_HPP */