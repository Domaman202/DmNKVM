#pragma once
#ifndef DMNKVM_KVMTYPES_HPP
#define DMNKVM_KVMTYPES_HPP

#include <KVMNamespace.hpp>
#include <KVMNameble.hpp>
#include <KVMConfig.hpp>
#include <KVMJP.hpp>
#include <DmNSTD.hpp>

#include <malloc.h>
#include <cstdint>
#include <utility>

namespace DmN::KVM {
    /// Хрень которая имеет низкоуровневый тип объекта
    struct LLT {
        explicit LLT(uint8_t llt) {
            this->llt = llt;
        }
        /// (Low Level Type) низкоуровневый тип обьякта: VARIABLE (0), FIELD (1), METHOD (2), LAMBDA (3), ENUM (4), STRUCT (5), CLASS (6)
        uint8_t llt : 3;
    };

    /// Объект подвергающийся сборке мусора
    struct GC_Object {
        explicit GC_Object(bool isCollectable) {
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
    struct Value_t : GC_Object {
        explicit Value_t(void* value, uint8_t type, bool isCollectable) : GC_Object(isCollectable) {
            this->type = type;
            this->value = value;
        }
        /// Тип значения: INT8 (1), INT16 (2), INT32 (3), INT64 (4), UINT8 (5), UINT16 (6), UINT32 (7), UINT64 (8), FLOAT (9), DOUBLE (10), CHAR (11), REFERENCE (12), OBJECT (13)
        uint8_t type : 4;
        /// Значение
        void* value;
    };

    /// Локальная переменная
    struct LocalVariable_t : LLT, Value_t, Nameble {
        LocalVariable_t(SI_t name, void* value, uint8_t type, bool isCollectable) : LLT(0), Value_t(value, type, isCollectable), Nameble(name) { }
    };

    /// Переменная
    struct Variable_t : LocalVariable_t, NSObject {
        Variable_t(SI_t name, NSI_t ns, void* value, uint8_t type, bool isCollectable) : LocalVariable_t(name, value, type, isCollectable), NSObject(ns) { }
    };

    /// Лямбда
    struct Lambda_t : LLT, GC_Object {
        explicit Lambda_t(SI_t descriptor, uint32_t cs, uint8_t* code) : LLT(3), GC_Object(true) {
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
    struct Field_t : LLT, Nameble {
        explicit Field_t(SI_t name, Value_t *value) : LLT(1), Nameble(name) {
            this->value = value;
        }
        /// Значение
        Value_t* value;
    };

    /// Метод
    struct Method_t : LLT, Nameble, NSObject {
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

    /// Универсальная основа для Enum-а
    struct EnumBase : LLT, Nameble, NSObject {
        explicit EnumBase(SI_t name, NSI_t ns, Value_t** enums, uint32_t enumsCount) : LLT(4), Nameble(name), NSObject(ns)  {
            this->enums = enums;
            this->enumsCount = enumsCount;
        }
        /// Перечисления
        Value_t** enums;
        /// Кол-во перечислений
        uint32_t enumsCount : 8;
    };

    struct Enum_8bit_t : EnumBase { uint8_t enums_size; };
    struct Enum_16bit_t : Enum_8bit_t { uint16_t enums_size; };
    struct Enum_32bit_t : Enum_16bit_t { uint32_t enums_size; };

    struct StructBase : LLT, Nameble, NSObject {
        explicit StructBase(SI_t name, NSI_t ns, Field_t** fields, uint32_t fieldsCount, CI_t* parents, uint8_t parentsCount) : LLT(5), Nameble(name), NSObject(ns) {
            this->fields = fields;
            this->fieldsCount = fieldsCount;
            this->parents = parents;
            this->parentsCount = parentsCount;
        }
        /// Поля
        Field_t** fields;
        /// Кол-во полей
        uint32_t fieldsCount : 8;
        /// Предки (ID предков)
        CI_t* parents;
        /// Кол-во предков
        uint8_t parentsCount : 5;
    };

    struct Struct_8bit_t : StructBase { uint8_t fieldsCount; };
    struct Struct_16bit_t : Struct_8bit_t { uint16_t fieldsCount; };
    struct Struct_32bit_t : Struct_16bit_t { uint32_t fieldsCount; };

    /// Универсальная основа для Class-а
    struct ClassBase : LLT, Nameble, NSObject {
        explicit ClassBase(SI_t name, NSI_t ns, Field_t** fields, uint32_t fieldsCount, Method_t** methods, uint32_t methodsCount, CI_t* parents, uint8_t parentsCount) : LLT(6), Nameble(name), NSObject(ns) {
            this->fields = fields;
            this->fieldsCount = fieldsCount;
            this->methods = methods;
            this->methodsCount = methodsCount;
            this->parents = parents;
            this->parentsCount = parentsCount;
        }
        /// Массив полей
        Field_t** fields;
        /// Кол-во полей
        uint32_t fieldsCount : 8;
        /// Массив методов
        Method_t** methods;
        /// Кол-во методов
        uint32_t methodsCount : 8;
        /// Предки (ID предков)
        CI_t* parents;
        /// Кол-во предков
        uint8_t parentsCount : 5;
    };

    struct Class_8bit_t : ClassBase { uint8_t fieldsCount; uint8_t methodsCount; };
    struct Class_16bit_t : Class_8bit_t { uint16_t fieldsCount; uint16_t methodsCount; };
    struct Class_32bit_t : Class_16bit_t { uint32_t fieldsCount; uint32_t methodsCount; };

    /// Абстрактная куча
    struct Heap {
        virtual CI_t addNew(ClassBase* clazz) = 0;
        virtual CI_t add(ClassBase* clazz) = 0;
        virtual void replace(ClassBase* clazz, CI_t id) = 0;
        virtual void remove(ClassBase* clazz) = 0;
        virtual void remove(CI_t id) = 0;
        virtual CI_t get(ClassBase* clazz) = 0;
        virtual ClassBase* get(CI_t id) = 0;
        //
        virtual ::std::pair<ClassBase**, size_t> getParents(ClassBase* clazz) = 0;
        virtual ::std::pair<ClassBase**, size_t> getParents(CI_t clazz) = 0;
    };

    /// Абстрактный загрузчик объектов
    struct ClassLoader {
        /* JVM */
        virtual ClassBase* defineJVMClass(int8_t* bytes, size_t off, size_t len) = 0;
        virtual ClassBase* defineJVMClass(JP::Java_class_file* file) = 0;
        /* .NET */
        // TODO: нужно реализовать
        /* KVM */
        virtual ClassBase* defineKVMClass(int8_t* bytes, size_t off, size_t len) = 0;
        virtual StructBase* defineKVMStruct(int8_t* bytes, size_t off, size_t len) = 0;
        virtual EnumBase* defineKVMEnum(int8_t* bytes, size_t off, size_t len) = 0;
        virtual Method_t* defineKVMMethod(int8_t* bytes, size_t off, size_t len) = 0;
        virtual Field_t* defineKVMField(int8_t* bytes, size_t off, size_t len) = 0;
        /* Low Level Operations */
        // Создание класса
        virtual ClassBase* createClass(Field_t** fields, uint8_t fields_size, Method_t** methods, uint8_t methods_size, CI_t* parents, uint8_t parents_size) = 0;
        virtual ClassBase* createClass(Field_t** fields, uint16_t fields_size, Method_t** methods, uint16_t methods_size, CI_t* parents, uint8_t parents_size) = 0;
        virtual ClassBase* createClass(Field_t** fields, uint32_t fields_size, Method_t** methods, uint32_t methods_size, CI_t* parents, uint8_t parents_size) = 0;
        // Создание структуры
        virtual StructBase* createStruct(Field_t** fields, uint8_t fields_size, CI_t* parents, uint8_t parents_size) = 0;
        virtual StructBase* createStruct(Field_t** fields, uint16_t fields_size, CI_t* parents, uint8_t parents_size) = 0;
        virtual StructBase* createStruct(Field_t** fields, uint32_t fields_size, CI_t* parents, uint8_t parents_size) = 0;
        // Создание Enum-а
        virtual EnumBase* createEnum(Variable_t** enums, uint8_t enums_size) = 0;
        virtual EnumBase* createEnum(Variable_t** enums, uint16_t enums_size) = 0;
        virtual EnumBase* createEnum(Variable_t** enums, uint32_t enums_size) = 0;
    };
}

#endif /* DMNKVM_KVMTYPES_HPP */