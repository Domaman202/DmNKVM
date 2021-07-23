#pragma once
#ifndef DMNKVM_HPP
#define DMNKVM_HPP

namespace DmN::KVM {
    struct Nameble;
    struct NaI;
    class NameStorage;
    //
    struct Enum_t;
    struct Struct_t;
    struct Class_t;
    //
    struct Field_t;
    struct Method_t;
    //
    /// Global Name Storage
    NameStorage* GNS;
}

#endif /* DMNKVM_HPP */