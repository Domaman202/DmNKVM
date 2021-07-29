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
        /// (Low Level Type) низкоуровневый тип обьякта: PUBLIC, STATIC, ENUM, STRUCT, Java_class
        uint8_t llt : 3;
    };

    /// Объект подвергающийся сборке мусора
    struct GC_Object {
        /// Собран ли объект?
        bool is_collected : 1;
        /// Можно ли собирать объект?
        bool is_collectable : 1;
        /// Кол-во ссылок на объект
        uint16_t references : 10;
    };



    /// Значение
    struct Value_t : GC_Object {
        /// Тип значения: INT8 (1), INT16 (2), INT32 (3), INT64 (4), UINT8 (5), UINT16 (6), UINT32 (7), UINT64 (8), FLOAT (9), DOUBLE (10), CHAR (11), REFERENCE (12), OBJECT (13)
        uint8_t type : 4;
        /// Значение
        void* value;
    };

    /// Переменная
    struct Variable_t : Value_t, Nameble, NSObject {
        /// Тип переменной: INT8 (1), INT16 (2), INT32 (3), INT64 (4), UINT8 (5), UINT16 (6), UINT32 (7), UINT64 (8), FLOAT (9), DOUBLE (10), CHAR (11), REFERENCE (12), OBJECT (13)
        uint8_t type : 4;
        /// Значение переменной
        void* value;
    };

    /// Лямбда
    struct Lambda_t : GC_Object {
        /// ID дескриптора
        SI_t descriptor;
        /// Размер байт-кода
        uint32_t code_size;
        /// Байт-код
        uint8_t* code;
    };

    /// Поле
    struct Field_t : LLT, Nameble {
        /// Значение
        Value_t* value;
    };

    /// Метод
    struct Method_t : Nameble, NSObject {
        /// ID дескриптора
        SI_t descriptor;
        /// Размер байт-кода
        uint32_t code_size;
        /// Байт-код
        uint8_t* code;
    };

    /// Универсальная основа для Enum-а
    struct Enum_base : LLT, Nameble, NSObject {
        /// Перечисления
        Variable_t** enums;
        /// Кол-во перечислений
        uint32_t enums_size : 8;
        //
        const uint8_t llt : 3 = 1;
    };

    struct Enum_8bit_t : Enum_base { uint8_t enums_size; };
    struct Enum_16bit_t : Enum_8bit_t { uint16_t enums_size; };
    struct Enum_32bit_t : Enum_16bit_t { uint32_t enums_size; };

    struct Struct_base : LLT, Nameble, NSObject {
        /// Поля
        Field_t** fields;
        /// Кол-во полей
        uint32_t fields_size : 8;
        /// Предки (ID предков)
        CI_t* parents;
        /// Кол-во предков
        uint8_t parents_size : 5;
        //
        const uint8_t llt : 3 = 2;
    };

    struct Struct_8bit_t : Struct_base { uint8_t fields_size; };
    struct Struct_16bit_t : Struct_8bit_t { uint16_t fields_size; };
    struct Struct_32bit_t : Struct_16bit_t { uint32_t fields_size; };

    /// Универсальная основа для Class-а
    struct Class_base : LLT, Nameble, NSObject {
        /// Массив полей
        Field_t** fields;
        /// Кол-во полей
        uint32_t fields_size : 8;
        /// Массив методов
        Method_t** methods;
        /// Кол-во методов
        uint32_t methods_size : 8;
        /// Предки (ID предков)
        CI_t* parents;
        /// Кол-во предков
        uint8_t parents_size : 5;
        //
        const uint8_t llt : 3 = 3;
    };

    struct Class_8bit_t : Class_base { uint8_t fields_size; uint8_t methods_size; };
    struct Class_16bit_t : Class_8bit_t { uint16_t fields_size; uint16_t methods_size; };
    struct Class_32bit_t : Class_16bit_t { uint32_t fields_size; uint32_t methods_size; };

    /// Абстрактная куча
    struct Heap {
        virtual CI_t addNewClass(Class_base* clazz) = 0;
        virtual CI_t addClass(Class_base* clazz) = 0;
        virtual void replaceClass(Class_base* clazz, CI_t id) = 0;
        virtual void removeClass(Class_base* clazz) = 0;
        virtual void removeClass(CI_t id) = 0;
        virtual CI_t getClassId(Class_base* clazz) = 0;
        virtual Class_base* getClass(CI_t id) = 0;
        //
        virtual ::std::pair<Class_base**, size_t> getClassParents(Class_base* clazz) = 0;
        virtual ::std::pair<Class_base**, size_t> getClassParents(CI_t clazz) = 0;
    };

    /// Абстрактный загрузчик объектов
    struct ClassLoader {
        /* JVM */
        virtual Class_base* defineJVMClass(int8_t* bytes, size_t off, size_t len) = 0;
        virtual Class_base* defineJVMClass(JP::Java_class_file* file) = 0;
        /* .NET */
        // TODO: нужно реализовать
        /* KVM */
        virtual Class_base* defineKVMClass(int8_t* bytes, size_t off, size_t len) = 0;
        virtual Struct_base* defineKVMStruct(int8_t* bytes, size_t off, size_t len) = 0;
        virtual Enum_base* defineKVMEnum(int8_t* bytes, size_t off, size_t len) = 0;
        virtual Method_t* defineKVMMethod(int8_t* bytes, size_t off, size_t len) = 0;
        virtual Field_t* defineKVMField(int8_t* bytes, size_t off, size_t len) = 0;
        /* Low Level Operations */
        // Создание класса
        virtual Class_base* createClass(Field_t** fields, uint8_t fields_size, Method_t** methods, uint8_t methods_size, CI_t* parents, uint8_t parents_size) = 0;
        virtual Class_base* createClass(Field_t** fields, uint16_t fields_size, Method_t** methods, uint16_t methods_size, CI_t* parents, uint8_t parents_size) = 0;
        virtual Class_base* createClass(Field_t** fields, uint32_t fields_size, Method_t** methods, uint32_t methods_size, CI_t* parents, uint8_t parents_size) = 0;
        // Создание структуры
        virtual Struct_base* createStruct(Field_t** fields, uint8_t fields_size, CI_t* parents, uint8_t parents_size) = 0;
        virtual Struct_base* createStruct(Field_t** fields, uint16_t fields_size, CI_t* parents, uint8_t parents_size) = 0;
        virtual Struct_base* createStruct(Field_t** fields, uint32_t fields_size, CI_t* parents, uint8_t parents_size) = 0;
        // Создание Enum-а
        virtual Enum_base* createEnum(Variable_t** enums, uint8_t enums_size) = 0;
        virtual Enum_base* createEnum(Variable_t** enums, uint16_t enums_size) = 0;
        virtual Enum_base* createEnum(Variable_t** enums, uint32_t enums_size) = 0;
    };
}

#endif /* DMNKVM_KVMTYPES_HPP */