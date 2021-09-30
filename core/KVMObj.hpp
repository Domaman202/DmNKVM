#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_OBJ_HPP
#define DMN_KVM_OBJ_HPP

#include "KVMTypes.hpp"

namespace DmN::KVM {
    /// Объект
    struct Object_t {
        /// Тип объекта
        struct Instanceble_t *type;
    };

    class EnumObject_t : public FieldStorage_t {
    public:
        /// Тип объекта
        struct Enum_t *type;
        /// Значения
        Value_t **values;
        /// Кол-во значений
        uint8_t values_count;

        SDL::DmNCollection<Field_t> *getFields() override {
            return nullptr; // TODO:
        }
    };

    class StructObject_t : public FieldStorage_t {
    public:
        /// Тип объекта
        struct Struct_t *type;
        /// Поля
        Field_t **fields;
        /// Кол-во полей
        uint8_t fields_count;

        SDL::DmNCollection<Field_t> *getFields() override {
            return nullptr; // TODO:
        }
    };

    class ClassObject_t : public StructObject_t {
    public:
        /// Тип объекта
        struct Class_t *type;
    };

    class EnumClassObject : public EnumObject_t, public ClassObject_t {
    public:
        SDL::DmNCollection<Field_t> *getFields() override {
            return nullptr; // TODO:
        }
    };

    /// Динамический объект
    class DynamicObject_t : public ClassObject_t, public MethodStorage_t {
    public:
        /// Методы объекта
        Method_t **methods;
        /// Кол-во методов
        uint8_t methods_count;

        SDL::DmNCollection<Method_t> *getMethods() override {
            return nullptr; // TODO:
        }
    };

    class DCVObject_t : public DynamicObject_t, public EnumClassObject {
    public:
        SDL::DmNCollection<Field_t> *getFields() override {
            return nullptr; // TODO:
        }
    };
}

#endif /* DMN_KVM_OBJ_HPP */
