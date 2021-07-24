#pragma once
#ifndef DMNKVM_HPP
#define DMNKVM_HPP

namespace DmN::KVM {
    struct Nameble;
    struct SaI;
    class StringStorage;
    //
    struct GC_Object;
    //
    struct LLT;
    //
    struct Enum_base;
    struct Enum_8bit_t;
    struct Enum_16bit_t;
    struct Enum_32bit_t;
    //
    struct Struct_base;
    struct Struct_8bit_t;
    struct Struct_16bit_t;
    struct Struct_32bit_t;
    //
    struct Class_base;
    struct Class_8bit_t;
    struct Class_16bit_t;
    struct Class_32bit_t;
    //
    struct Field_t;
    struct Method_t;
    //
    struct Value_t;
    struct Variable_t;
    struct Lambda_t;
    //
    /// (Global Name Storage) Глобальное хранилище имён
    StringStorage* GNS;
    /// (Global Descriptor Storage) Глобальное хранилище дескрипторов
    StringStorage* GDS;
}

#endif /* DMNKVM_HPP */