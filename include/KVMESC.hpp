#pragma once
#ifndef DMNKVM_KVMESC_HPP
#define DMNKVM_KVMESC_HPP

#include <KVMConfig.hpp>
#include <KVMTypes.hpp>
#include <KVMLLT.hpp>

#include <cstdint>

namespace DmN::KVM {
    /// Универсальная основа для Enum-а
    exStruct(EnumBase) : LLT, Nameble, NSObject {
        explicit EnumBase(SI_t
                          name,
                          NSI_t ns, Value_t
                          **enums,
                          uint32_t enumsCount) : LLT(4), Nameble(name), NSObject(ns) {
            this->enums = enums;
            this->enumsCount = enumsCount;
        }

        /// Перечисления
        Value_t **enums;
        /// Кол-во перечислений
        uint32_t enumsCount: 8;
    };

    struct Enum_8bit_t : EnumBase {
        uint8_t enums_size;
    };
    struct Enum_16bit_t : Enum_8bit_t {
        uint16_t enums_size;
    };
    struct Enum_32bit_t : Enum_16bit_t {
        uint32_t enums_size;
    };

    exStruct(StructBase) : LLT, Nameble, NSObject {
        explicit StructBase(SI_t name,
                            NSI_t ns, Field_t
                            **fields,
                            uint32_t fieldsCount, CI_t
                            *parents,
                            uint8_t parentsCount) : LLT(5), Nameble(name), NSObject(ns) {
            this->fields = fields;
            this->fieldsCount = fieldsCount;
            this->parents = parents;
            this->parentsCount = parentsCount;
        }

        /// Поля
        Field_t **fields;
        /// Кол-во полей
        uint32_t fieldsCount: 8;
        /// Предки (ID предков)
        CI_t *parents;
        /// Кол-во предков
        uint8_t parentsCount: 5;
    };

    struct Struct_8bit_t : StructBase {
        uint8_t fieldsCount;
    };
    struct Struct_16bit_t : Struct_8bit_t {
        uint16_t fieldsCount;
    };
    struct Struct_32bit_t : Struct_16bit_t {
        uint32_t fieldsCount;
    };

    /// Универсальная основа для Class-а
    struct ClassBase : LLT, Nameble, NSObject {
        explicit ClassBase(SI_t name, NSI_t ns, Field_t **fields, uint32_t fieldsCount, Method_t **methods,
                           uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) : LLT(6), Nameble(name),
                                                                                         NSObject(ns) {
            this->fields = fields;
            this->fieldsCount = fieldsCount;
            this->methods = methods;
            this->methodsCount = methodsCount;
            this->parents = parents;
            this->parentsCount = parentsCount;
        }

        /// Массив полей
        Field_t **fields;
        /// Кол-во полей
        uint32_t fieldsCount: 8;
        /// Массив методов
        Method_t **methods;
        /// Кол-во методов
        uint32_t methodsCount: 8;
        /// Предки (ID предков)
        CI_t *parents;
        /// Кол-во предков
        uint8_t parentsCount: 5;
    };

    struct Class_8bit_t : ClassBase {
        uint8_t fieldsCount;
        uint8_t methodsCount;
    };
    struct Class_16bit_t : Class_8bit_t {
        uint16_t fieldsCount;
        uint16_t methodsCount;
    };
    struct Class_32bit_t : Class_16bit_t {
        uint32_t fieldsCount;
        uint32_t methodsCount;
    };
}

#endif /* DMNKVM_KVMESC_HPP */