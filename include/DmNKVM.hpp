#pragma once
#ifndef DMNKVM_HPP
#define DMNKVM_HPP

namespace DmN::KVM {
    struct Nameble;
    struct NaI;
    class NameStorage;
    //
    struct GC_Object;
    //
    struct Class_base;
    struct Class_base_8bit;
    struct Class_base_16bit;
    struct Class_base_32bit;
    //
    struct Enum_t;
    struct Struct_t;
    struct Class_t;
    //
    struct Field_t;
    struct Method_t;
    //
    struct Variable_t;
    //
    /// Global Name Storage
    NameStorage* GNS;
}

#endif /* DMNKVM_HPP */