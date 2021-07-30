#pragma once
#ifndef DMNKVM_KVM_HPP
#define DMNKVM_KVM_HPP

#include <KVMTypes.hpp>
#include <KVMNameble.hpp>

namespace DmN::KVM {
#ifdef DMN_KVM_USE_GLOBAL_NAME_STORAGES
    /// (Global Name Storage) Глобальное хранилище имён
    SS* GNS = new DSS();
    /// (Global Descriptor Storage) Глобальное хранилище дескрипторов
    SS* GDS = new DSS();
#endif
}

#endif /* DMNKVM_KVM_HPP */
