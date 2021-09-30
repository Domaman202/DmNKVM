#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_CLASSLOADER_HPP
#define DMN_KVM_CLASSLOADER_HPP

#include "KVMESC.hpp"

namespace DmN::KVM {
    /// Абстрактный загрузчик объектов
    struct ClassLoader {
        /* JVM */
        virtual Class_t *defineJVMClass(int8_t *bytes, size_t off, size_t len) = 0;
        /* .NET */
        // TODO: нужно реализовать
        /* KVM */
        virtual Class_t *defineKVMClass(int8_t *bytes, size_t off, size_t len) = 0;

        virtual Struct_t *defineKVMStruct(int8_t *bytes, size_t off, size_t len) = 0;

        virtual Enum_t *defineKVMEnum(int8_t *bytes, size_t off, size_t len) = 0;

        virtual Method_t *defineKVMMethod(int8_t *bytes, size_t off, size_t len) = 0;

        virtual Field_t *defineKVMField(int8_t *bytes, size_t off, size_t len) = 0;
        /* Low Level Operations */
        // Создание класса
        virtual Class_t *
        createClass(Field_t **fields, uint8_t fields_size, Method_t **methods, uint8_t methods_size, CI_t *parents,
                    uint8_t parents_size) = 0;

        virtual Class_t *
        createClass(Field_t **fields, uint16_t fields_size, Method_t **methods, uint16_t methods_size,
                    CI_t *parents, uint8_t parents_size) = 0;

        virtual Class_t *
        createClass(Field_t **fields, uint32_t fields_size, Method_t **methods, uint32_t methods_size,
                    CI_t *parents, uint8_t parents_size) = 0;

        // Создание структуры
        virtual Struct_t *
        createStruct(Field_t **fields, uint8_t fields_size, CI_t *parents, uint8_t parents_size) = 0;

        virtual Struct_t *
        createStruct(Field_t **fields, uint16_t fields_size, CI_t *parents, uint8_t parents_size) = 0;

        virtual Struct_t *
        createStruct(Field_t **fields, uint32_t fields_size, CI_t *parents, uint8_t parents_size) = 0;

        // Создание Enum-а
        virtual Enum_t *createEnum(Variable_t **enums, uint8_t enums_size) = 0;

        virtual Enum_t *createEnum(Variable_t **enums, uint16_t enums_size) = 0;

        virtual Enum_t *createEnum(Variable_t **enums, uint32_t enums_size) = 0;
    };
}

#endif /* DMN_KVM_CLASSLOADER_HPP */