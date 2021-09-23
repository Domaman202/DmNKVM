#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_TYPES_HPP
#define DMN_KVM_TYPES_HPP

#include <KVMNM.hpp>
#include <KVMNameble.hpp>
#include <KVMLLT.hpp>

#include <cstdlib>

namespace DmN::KVM {
    /// Объект подвергающийся сборке мусора
    struct GCObject {
        explicit GCObject(bool isCollectable) {
            this->isCollectable = isCollectable;
            this->isCollected = false;
            this->references = 0;
        }

        /// Собран ли объект?
        bool isCollected: 1;
        /// Можно ли собирать объект?
        bool isCollectable: 1;
        /// Кол-во ссылок на объект
        uint16_t references: 10;
    };

    /// Значение
    struct Value_t : GCObject {
        explicit Value_t(void *value, uint8_t type, bool isCollectable) : GCObject(isCollectable) {
            this->type = type;
            this->value = value;
        }

        /// Тип значения: INT8 (1), INT16 (2), INT32 (3), INT64 (4), UINT8 (5), UINT16 (6), UINT32 (7), UINT64 (8), FLOAT (9), DOUBLE (10), CHAR (11), REFERENCE (12), OBJECT (13)
        uint8_t type: 4;
        /// Значение
        void *value;
    };

    /// Переменная
    struct Variable_t : LLT, Value_t, Nameble {
        Variable_t(SI_t name, void *value, uint8_t type, bool isCollectable) : LLT(0),
                                                                               Value_t(value, type, isCollectable),
                                                                               Nameble(name) {}
    };

    /// Лямбда
    class Lambda_t : LLT, GCObject {
        explicit Lambda_t(SI_t descriptor, uint32_t cs, uint8_t *code) : LLT(3), GCObject(true) {
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
    class Field_t : LLT, Nameble {
    public:
        explicit Field_t(SI_t name, Value_t *value) : LLT(1), Nameble(name) {
            this->value = value;
        }

        /// Значение
        Value_t *value;
    };

    /// Метод
    class Method_t : LLT, Nameble {
        explicit Method_t(SI_t descriptor) : LLT(2), Nameble(descriptor) {
            this->name = descriptor;
        }

        /// ID дескриптора
        SI_t name;
    };

    /// Метод
    class NSMethod_t : Method_t, NSObject {
        explicit NSMethod_t(SI_t descriptor, NSI_t ns) : Method_t(descriptor), NSObject(ns) {
            this->name = descriptor;
        }

        /// ID дескриптора
        SI_t name;
    };

    class BCMethod_t : Method_t {
    public:
        explicit BCMethod_t(SI_t descriptor, uint32_t cs, uint8_t *code) : Method_t(descriptor) {
            this->cs = cs;
            this->code = code;
        }

        /// (Code Size) Размер байт-кода
        uint32_t cs;
        /// Байт-код
        uint8_t *code;
    };

    class NSBCMethod_t : BCMethod_t, NSMethod_t {
    public:
        explicit NSBCMethod_t(SI_t descriptor, uint32_t cs, uint8_t *code) : BCMethod(descriptor, cs, code),
                                                                             NSMethod_t(descriptor, ns) {
        }
    };

    class NMethod_t : Method_t {
    public:
        explicit NMethod(SI_t
        descriptor) :
        Method_t(descriptor) {
        }

        virtual Value_t *execute(Value_t **args) = 0;

        virtual Value_t *execute(void *obj, Value_t **args) = 0;
    };

    class NSNMethod_t : NMethod_t, NSMethod_t {
    public:
        explicit NSNMethod_t(SI_t descriptor, NSI_t ns) : NMethod_t(descriptor), NSMethod_t(descriptor, ns) {}
    };

    typedef Value_t *(KVMMethod)(void *obj, Value_t **args);

    class NRMethod_t : NMethod {
    public:
        explicit NRMethod_t(KVMMethod *method, SI_t descriptor) : NMethod_t(descriptor) {
            this->ref = method;
        }

        Value_t *execute(Value_t **args) override {
            return ref(nullptr, args);
        }

        Value_t *execute(void *obj, Value_t **args) override {
            return ref(obj, args);
        }

        KVMMethod *ref;
    };

    class NSNRMethod_t : NRMethod_t, NSMethod_t {
    public:
        explicit NSNRMethod_t(KVMMethod *method, SI_t descriptor, NSI_t ns) : NRMethod_t(method, descriptor),
                                                                              NSMethod_t(descriptor, ns) {
        }
    };
}

#endif /* DMN_KVM_TYPES_HPP */