#pragma once
#ifndef DMNKVM_KVMGLOBALS_HPP
#define DMNKVM_KVMGLOBALS_HPP

#include <KVMNameble.hpp>

namespace DmN::KVM {
#ifdef DMN_KVM_USE_GLOBAL_NAME_STORAGES
    /// (Global Name Storage) Глобальное хранилище имён
    DMN_KVM_EI(auto*, GNS, new DSS());
    /// (Global Descriptor Storage) Глобальное хранилище дескрипторов
    DMN_KVM_EI(auto*, GDS, new DSS());
#endif
}

#endif /* DMNKVM_KVMGLOBALS_HPP */
