#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_ESC_HPP
#define DMN_KVM_ESC_HPP

#include "KVMTypes.hpp"
#include <cstdint>

namespace DmN::KVM {
    /// Объект (нет) который может быть инстансирован
    struct Instanceble_t {
        virtual struct Object_t *newInstance(Value_t **args, size_t args_c) { return nullptr; };
    };

    /// Универсальная основа для Enum-а
    struct Enum_t : public LLTNameble, public Modifiable, public Instanceble_t, public FieldStorage_t {
        explicit Enum_t(SI_t name,
                        uint8_t modifier,
                        Value_t **enums,
                        SI_t *names,
                        uint8_t enumsCount) : LLTNameble(name, LLTypes::ENUM), Modifiable(modifier) {
            this->enums = enums;
            this->names = names;
            this->enumsCount = enumsCount;
        }

        SDL::DmNCollection *getFields() override {
            return nullptr; // TODO:
        }

        struct Object_t *newInstance(Value_t **args, size_t args_c) override {
            return nullptr; // TODO:
        }

        /// Перечисления
        Value_t **enums;
        /// Имена перечислений
        SI_t *names;
        /// Кол-во перечислений
        uint8_t enumsCount;
    };

    /// Универсальная основа для структуры
    struct Struct_t : public LLTNameble, public Modifiable, public Instanceble_t, public FieldStorage_t {
        explicit Struct_t(SI_t name,
                          uint8_t modifier,
                          Field_t **fields,
                          uint8_t fieldsCount,
                          CI_t *parents,
                          uint8_t parentsCount) : LLTNameble(name, LLTypes::STRUCT), Modifiable(modifier) {
            this->fields = fields;
            this->fieldsCount = fieldsCount;
            this->parents = parents;
            this->parentsCount = parentsCount;
        }

        SDL::DmNCollection *getFields() override {
            return nullptr; // TODO:
        }

        struct Object_t *newInstance(Value_t **args, size_t args_c) override {
            return nullptr; // TODO:
        }

        /// Поля
        Field_t **fields;
        /// Кол-во полей
        uint8_t fieldsCount;
        /// Предки (ID предков)
        CI_t *parents;
        /// Кол-во предков
        uint8_t parentsCount: 5;
    };

    /// Универсальная основа для Class-а
    class Class_t
            : public LLTNameble,
              public Modifiable,
              public Instanceble_t,
              public FieldStorage_t,
              public MethodStorage_t {
    public:
        explicit Class_t(SI_t name, uint8_t modifier, Field_t **fields, uint8_t fieldsCount, Method_t **methods,
                         uint8_t methodsCount, CI_t *parents, uint8_t parentsCount) : LLTNameble(name,
                                                                                                 LLTypes::CLASS),
                                                                                      Modifiable(modifier) {
            this->fields = fields;
            this->fieldsCount = fieldsCount;
            this->methods = methods;
            this->methodsCount = methodsCount;
            this->parents = parents;
            this->parentsCount = parentsCount;
        }

        SDL::DmNCollection *getFields() override {
            return nullptr; // TODO:
        }

        SDL::DmNCollection *getMethods() override {
            return nullptr; // TODO:
        }

        struct Object_t *newInstance(Value_t **args, size_t args_c) override {
            return nullptr; // TODO:
        }

        /// Массив полей
        Field_t **fields;
        /// Кол-во полей
        uint8_t fieldsCount;
        /// Массив методов
        Method_t **methods;
        /// Кол-во методов
        uint8_t methodsCount;
        /// Предки (ID предков)
        CI_t *parents;
        /// Кол-во предков
        uint8_t parentsCount: 5;
    };

    /// Основа класса со встроенными классами
    class ISClass_t : public Class_t {
    public:
        explicit ISClass_t(Class_t *base, SI_t name, uint8_t modifier, Field_t **fields,
                           uint32_t fieldsCount,
                           Method_t **methods,
                           uint32_t methodsCount, CI_t *parents, uint8_t parentsCount) : Class_t(name,
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
        Class_t *base;
    };

    class EnumClass_t : public Class_t, public Enum_t {
        SDL::DmNCollection *getFields() override {
            return nullptr; // TODO:
        }

        SDL::DmNCollection *getMethods() override {
            return nullptr; // TODO:
        }
    };
}

#endif /* DMN_KVM_ESC_HPP */