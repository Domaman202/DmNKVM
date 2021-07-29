#pragma once
#ifndef DMNKVM_KVMNAMESPACE_HPP
#define DMNKVM_KVMNAMESPACE_HPP

#include <KVMNameble.hpp>
#include <KVMConfig.hpp>

#include <cstdint>

namespace DmN::KVM {
    /// Пространство имён
    struct Namespace : Nameble {
        Namespace* parent;
    };

    /// (Namespace Object) Объект который подчинаеться пространству имён
    struct NSObject {
        SI_t namespace_id;
    };

    /// (Namespace Storage) Хранилище пространств имён
    struct NSStorage {
        virtual SI_t addNewNamespace(Namespace* ns) = 0;
        virtual SI_t addNamespace(Namespace* ns) = 0;
    };
}

#endif /* DMNKVM_KVMNAMESPACE_HPP */
