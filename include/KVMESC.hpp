#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_ESC_HPP
#define DMN_KVM_ESC_HPP

#include "KVMTypes.hpp"
#include <cstdint>

namespace DmN::KVM {
    struct LLTNameble : Nameble, LLT {
        LLTNameble(SI_t name, uint8_t llt) : Nameble(name), LLT(llt) {}
    };

    /// Универсальная основа для Enum-а
    struct EnumBase : LLTNameble, Modifiable {
        explicit EnumBase(SI_t name,
                          uint8_t modifier,
                          Value_t **enums,
                          uint32_t enumsCount) : LLTNameble(name, 4), Modifiable(modifier) {
            this->enums = enums;
            this->enumsCount = enumsCount;
        }

        /// Перечисления
        Value_t **enums;
        /// Кол-во перечислений
        uint32_t enumsCount: 8;
    };

    struct NSEnumBase : EnumBase, NSObject {
        explicit NSEnumBase(SI_t name,
                            NSI_t ns,
                            uint8_t modifier,
                            Value_t **enums,
                            uint32_t enumsCount) : EnumBase(name, modifier, enums, enumsCount), NSObject(ns) {}
    };

    struct Enum_8bit_t : EnumBase {
        explicit Enum_8bit_t(SI_t name, uint8_t modifier, Value_t **enums, uint32_t enumsCount) : EnumBase(name,
                                                                                                           modifier,
                                                                                                           enums,
                                                                                                           enumsCount) {
            this->enumsCount = enumsCount;
        }

        uint8_t enumsCount;
    };

    struct Enum_16bit_t : Enum_8bit_t {
        explicit Enum_16bit_t(SI_t name, uint8_t modifier, Value_t **enums, uint32_t enumsCount) : Enum_8bit_t(name,
                                                                                                               modifier,
                                                                                                               enums,
                                                                                                               enumsCount) {
            this->enumsCount = enumsCount;
        }

        uint16_t enumsCount;
    };

    struct Enum_32bit_t : Enum_16bit_t {
        explicit Enum_32bit_t(SI_t name, uint8_t modifier, Value_t **enums, uint32_t enumsCount) : Enum_16bit_t(
                name,
                modifier,
                enums,
                enumsCount) {
            this->enumsCount = enumsCount;
        }

        uint32_t enumsCount;
    };

    /// Универсальная основа для структуры
    struct StructBase : LLTNameble, Modifiable {
        explicit StructBase(SI_t name,
                            uint8_t modifier,
                            Field_t **fields,
                            uint32_t fieldsCount,
                            CI_t *parents,
                            uint8_t parentsCount) : LLTNameble(name, 5), Modifiable(modifier) {
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
        explicit Struct_8bit_t(SI_t name,
                               uint8_t modifier,
                               Field_t **fields,
                               uint32_t fieldsCount,
                               CI_t *parents,
                               uint8_t parentsCount) : StructBase(name, modifier, fields, fieldsCount, parents,
                                                                  parentsCount) {
            this->fieldsCount = fieldsCount;
        }

        uint8_t fieldsCount;
    };

    struct Struct_16bit_t : Struct_8bit_t {
        explicit Struct_16bit_t(SI_t name,
                                uint8_t modifier,
                                Field_t **fields,
                                uint32_t fieldsCount,
                                CI_t *parents,
                                uint8_t parentsCount) : Struct_8bit_t(name, modifier, fields, fieldsCount, parents,
                                                                      parentsCount) {
            this->fieldsCount = fieldsCount;
        }

        uint16_t fieldsCount;
    };

    struct Struct_32bit_t : Struct_16bit_t {
        explicit Struct_32bit_t(SI_t name,
                                uint8_t modifier,
                                Field_t **fields,
                                uint32_t fieldsCount,
                                CI_t *parents,
                                uint8_t parentsCount) : Struct_16bit_t(name, modifier, fields, fieldsCount, parents,
                                                                       parentsCount) {
            this->fieldsCount = fieldsCount;
        }

        uint32_t fieldsCount;
    };

    /// Универсальная основа для Class-а
    class ClassBase : LLTNameble, Modifiable {
    public:
        explicit ClassBase(SI_t name, uint8_t modifier, Field_t **fields, uint32_t fieldsCount, Method_t **methods,
                           uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) : LLTNameble(name, 6),
                                                                                         Modifiable(modifier) {
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

    /// Основа класса со встроенными классами
    class InnerStorageClassBase : ClassBase {
    public:
        explicit InnerStorageClassBase(ClassBase *base, SI_t name, uint8_t modifier, Field_t **fields,
                                       uint32_t fieldsCount,
                                       Method_t **methods,
                                       uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) : ClassBase(name,
                                                                                                               modifier,
                                                                                                               fields,
                                                                                                               fieldsCount,
                                                                                                               methods,
                                                                                                               methodsCount,
                                                                                                               parents,
                                                                                                               parentsCount) {
            this->base = base;
        }

        /// Основной класс
        ClassBase *base;
    };

    class Class_8bit_t : ClassBase {
    public:
        explicit Class_8bit_t(SI_t name, uint8_t modifier, Field_t **fields, uint32_t fieldsCount,
                              Method_t **methods,
                              uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) : ClassBase(name,
                                                                                                      modifier,
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

    class Class_16bit_t : Class_8bit_t {
    public:
        explicit Class_16bit_t(SI_t name, uint8_t modifier, Field_t **fields, uint32_t fieldsCount,
                               Method_t **methods,
                               uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) : Class_8bit_t(name,
                                                                                                          modifier,
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

    class Class_32bit_t : Class_16bit_t {
    public:
        explicit Class_32bit_t(SI_t name, uint8_t modifier, Field_t **fields, uint32_t fieldsCount,
                               Method_t **methods,
                               uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) : Class_16bit_t(name,
                                                                                                           modifier,
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

    class InnerStorageClass_8bit_t : InnerStorageClassBase {
    public:
        explicit InnerStorageClass_8bit_t(ClassBase *base, SI_t name, uint8_t modifier, Field_t **fields,
                                          uint32_t fieldsCount,
                                          Method_t **methods,
                                          uint32_t methodsCount, CI_t *parents, uint8_t parentsCount)
                : InnerStorageClassBase(base,
                                        name,
                                        modifier,
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

    class InnerStorageClass_16bit_t : InnerStorageClass_8bit_t {
    public:
        explicit InnerStorageClass_16bit_t(ClassBase *base, SI_t name, uint8_t modifier, Field_t **fields,
                                           uint32_t fieldsCount,
                                           Method_t **methods,
                                           uint32_t methodsCount, CI_t *parents, uint8_t parentsCount)
                : InnerStorageClass_8bit_t(base,
                                           name,
                                           modifier,
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

    class InnerStorageClass_32bit_t : InnerStorageClass_16bit_t {
    public:
        explicit InnerStorageClass_32bit_t(ClassBase *base, SI_t name, uint8_t modifier, Field_t **fields,
                                           uint32_t fieldsCount,
                                           Method_t **methods,
                                           uint32_t methodsCount, CI_t *parents, uint8_t parentsCount)
                : InnerStorageClass_16bit_t(base,
                                            name,
                                            modifier,
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

#endif /* DMN_KVM_ESC_HPP */