#pragma once
#ifndef DMNKVM_KVMESC_HPP
#define DMNKVM_KVMESC_HPP

#include <KVMConfig.hpp>
#include <KVMNM.hpp>
#include <KVMTypes.hpp>
#include <KVMLLT.hpp>

#include <cstdint>

namespace DmN::KVM {
    /// Универсальная основа для Enum-а
    eStruct(EnumBase) : LLT, Nameble {
        explicit EnumBase(SI_t name,
                          Value_t **enums,
                          uint32_t enumsCount) : LLT(4), Nameble(name) {
            this->enums = enums;
            this->enumsCount = enumsCount;
        }

        /// Перечисления
        Value_t **enums;
        /// Кол-во перечислений
        uint32_t enumsCount: 8;
    };

    eStruct(NSEnumBase) : EnumBase, NSObject {
        explicit NSEnumBase(SI_t name,
                            NSI_t ns,
                            Value_t **enums,
                            uint32_t enumsCount) : EnumBase(name, enums, enumsCount), NSObject(ns) {}
    }

    struct Enum_8bit_t : EnumBase {
        uint8_t enums_size;
    };
    struct Enum_16bit_t : Enum_8bit_t {
        uint16_t enums_size;
    };
    struct Enum_32bit_t : Enum_16bit_t {
        uint32_t enums_size;
    };
    struct NSEnum_8bit_t : NSEnumBase {
        uint8_t enums_size;
    };
    struct NSEnum_16bit_t : NSEnum_8bit_t {
        uint16_t enums_size;
    };
    struct NSEnum_32bit_t : NSEnum_16bit_t {
        uint32_t enums_size;
    };

    eStruct(StructBase) : LLT, Nameble {
        explicit StructBase(SI_t name,
                            Field_t **fields,
                            uint32_t fieldsCount,
                            CI_t *parents,
                            uint8_t parentsCount) : LLT(5), Nameble(name) {
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

    eStruct(NSStructBase) : StructBase, NSObject {
        explicit NSStructBase(SI_t name,
                              NSI_t ns,
                              Field_t **fields,
                              uint32_t fieldsCount,
                              CI_t *parents,
                              uint8_t parentsCount) : StructBase(name, fields, fieldsCount, parents, parentsCount),
                                                      NSObject(ns) {}
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
    struct NSStruct_8bit_t : NSStructBase {
        uint8_t fieldsCount;
    };
    struct NSStruct_16bit_t : NSStruct_8bit_t {
        uint16_t fieldsCount;
    };
    struct NSStruct_32bit_t : NSStruct_16bit_t {
        uint32_t fieldsCount;
    };

    /// Универсальная основа для Class-а
    eStruct(ClassBase) : LLT, Nameble {
        explicit ClassBase(SI_t name, Field_t **fields, uint32_t fieldsCount, Method_t **methods,
                           uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) : LLT(6), Nameble(name) {
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

    eStruct(NSClassBase) : ClassBase, NSObject {
        explicit NSClassBase(SI_t name, NSI_t ns, Field_t **fields, uint32_t fieldsCount, Method_t **methods,
                             uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) : ClassBase(name, fields,
                                                                                                     fieldsCount,
                                                                                                     methods,
                                                                                                     methodsCount,
                                                                                                     parents,
                                                                                                     parentsCount),
                                                                                           NSObject(ns) {}
    };

    struct Class_8bit_t : ClassBase {
        explicit Class_8bit_t(SI_t name, Field_t **fields, uint32_t fieldsCount, Method_t **methods,
                              uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) : ClassBase(name, fields,
                                                                                                      fieldsCount,
                                                                                                      methods,
                                                                                                      methodsCount,
                                                                                                      parents,
                                                                                                      parentsCount) {
            this->fieldsCount = fieldsCount;
            this->methodsCount = methodsCount;
        }

        uint8_t fieldsCount;
        uint8_t methodsCount;
    };

    struct Class_16bit_t : Class_8bit_t {
        explicit Class_16bit_t(SI_t name, Field_t **fields, uint32_t fieldsCount, Method_t **methods,
                               uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) : Class_8bit_t(name, fields,
                                                                                                          fieldsCount,
                                                                                                          methods,
                                                                                                          methodsCount,
                                                                                                          parents,
                                                                                                          parentsCount) {
            this->fieldsCount = fieldsCount;
            this->methodsCount = methodsCount;
        }

        uint16_t fieldsCount;
        uint16_t methodsCount;
    };

    struct Class_32bit_t : Class_16bit_t {
        explicit Class_32bit_t(SI_t name, Field_t **fields, uint32_t fieldsCount, Method_t **methods,
                               uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) : Class_16bit_t(name, fields,
                                                                                                           fieldsCount,
                                                                                                           methods,
                                                                                                           methodsCount,
                                                                                                           parents,
                                                                                                           parentsCount) {
            this->fieldsCount = fieldsCount;
            this->methodsCount = methodsCount;
        }

        uint32_t fieldsCount;
        uint32_t methodsCount;
    };

    struct NSClass_8bit_t : NSClassBase {
        explicit NSClass_8bit_t(SI_t name, NSI_t ns, Field_t **fields, uint32_t fieldsCount, Method_t **methods,
                                uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) : NSClassBase(name, ns,
                                                                                                          fields,
                                                                                                          fieldsCount,
                                                                                                          methods,
                                                                                                          methodsCount,
                                                                                                          parents,
                                                                                                          parentsCount) {
            this->fieldsCount = fieldsCount;
            this->methodsCount = methodsCount;
        }

        uint8_t fieldsCount;
        uint8_t methodsCount;
    };

    struct NSClass_16bit_t : NSClass_8bit_t {
        explicit NSClass_16bit_t(SI_t name, NSI_t ns, Field_t **fields, uint32_t fieldsCount, Method_t **methods,
                                 uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) : NSClass_8bit_t(name, ns,
                                                                                                              fields,
                                                                                                              fieldsCount,
                                                                                                              methods,
                                                                                                              methodsCount,
                                                                                                              parents,
                                                                                                              parentsCount) {
            this->fieldsCount = fieldsCount;
            this->methodsCount = methodsCount;
        }

        uint16_t fieldsCount;
        uint16_t methodsCount;
    };

    struct NSClass_32bit_t : NSClass_16bit_t {
        explicit NSClass_32bit_t(SI_t name, NSI_t ns, Field_t **fields, uint32_t fieldsCount, Method_t **methods,
                                 uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) : NSClass_16bit_t(name, ns,
                                                                                                               fields,
                                                                                                               fieldsCount,
                                                                                                               methods,
                                                                                                               methodsCount,
                                                                                                               parents,
                                                                                                               parentsCount) {
            this->fieldsCount = fieldsCount;
            this->methodsCount = methodsCount;
        }

        uint32_t fieldsCount;
        uint32_t methodsCount;
    };
}

#endif /* DMNKVM_KVMESC_HPP */