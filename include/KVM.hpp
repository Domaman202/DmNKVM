#pragma once
#ifndef DMNKVM_KVM_HPP
#define DMNKVM_KVM_HPP

#include <KVMConfig.h>
#include <KVMTypes.hpp>

namespace DmN::KVM {
#ifdef DMN_KVM_USE_GLOBAL_NAME_STORAGES
    /// (Global Name Storage) Глобальное хранилище имён
    constinit StringStorage* GNS = new DynamicStringStorage;
    /// (Global Descriptor Storage) Глобальное хранилище дескрипторов
    constinit StringStorage* GDS = new DynamicStringStorage;
#endif
}

#endif /* DMNKVM_KVM_HPP */
