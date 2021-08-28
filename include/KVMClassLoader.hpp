#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_CLASSLOADER_HPP
#define DMN_KVM_CLASSLOADER_HPP

#inclued <KVMConfig.hpp>
#include <KVMESC.hpp>

namespace DmN::KVM {
    /// Абстрактный загрузчик объектов
    DMN_KVM_E struct ClassLoader {
        /* JVM */
        DMN_KVM_EE  virtual ClassBase* defineJVMClass(int8_t* bytes, size_t off, size_t len) = 0;
        /* .NET */
        // TODO: нужно реализовать
        /* KVM */
        DMN_KVM_EE virtual ClassBase* defineKVMClass(int8_t* bytes, size_t off, size_t len) = 0;
        DMN_KVM_EE virtual StructBase* defineKVMStruct(int8_t* bytes, size_t off, size_t len) = 0;
        DMN_KVM_EE virtual EnumBase* defineKVMEnum(int8_t* bytes, size_t off, size_t len) = 0;
        DMN_KVM_EE virtual Method_t* defineKVMMethod(int8_t* bytes, size_t off, size_t len) = 0;
        DMN_KVM_EE virtual Field_t* defineKVMField(int8_t* bytes, size_t off, size_t len) = 0;
        /* Low Level Operations */
        // Создание класса
        DMN_KVM_EE virtual ClassBase* createClass(Field_t** fields, uint8_t fields_size, Method_t** methods, uint8_t methods_size, CI_t* parents, uint8_t parents_size) = 0;
        DMN_KVM_EE virtual ClassBase* createClass(Field_t** fields, uint16_t fields_size, Method_t** methods, uint16_t methods_size, CI_t* parents, uint8_t parents_size) = 0;
        DMN_KVM_EE virtual ClassBase* createClass(Field_t** fields, uint32_t fields_size, Method_t** methods, uint32_t methods_size, CI_t* parents, uint8_t parents_size) = 0;
        // Создание структуры
        DMN_KVM_EE virtual StructBase* createStruct(Field_t** fields, uint8_t fields_size, CI_t* parents, uint8_t parents_size) = 0;
        DMN_KVM_EE virtual StructBase* createStruct(Field_t** fields, uint16_t fields_size, CI_t* parents, uint8_t parents_size) = 0;
        DMN_KVM_EE virtual StructBase* createStruct(Field_t** fields, uint32_t fields_size, CI_t* parents, uint8_t parents_size) = 0;
        // Создание Enum-а
        DMN_KVM_EE virtual EnumBase* createEnum(Variable_t** enums, uint8_t enums_size) = 0;
        DMN_KVM_EE virtual EnumBase* createEnum(Variable_t** enums, uint16_t enums_size) = 0;
        DMN_KVM_EE virtual EnumBase* createEnum(Variable_t** enums, uint32_t enums_size) = 0;
    };
}

#endif /* DMN_KVM_CLASSLOADER_HPP */