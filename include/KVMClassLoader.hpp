#pragma once
#ifndef DMNKVM_KVMCLASSLOADER_HPP
#define DMNKVM_KVMCLASSLOADER_HPP

#include <KVMJP.hpp>
#include <KVMESC.hpp>

namespace DmN::KVM {
    /// Абстрактный загрузчик объектов
    eStruct(ClassLoader) {
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

#endif /* DMNKVM_KVMCLASSLOADER_HPP */