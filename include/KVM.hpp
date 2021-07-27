#pragma once
#ifndef DMNKVM_KVM_HPP
#define DMNKVM_KVM_HPP

#include <KVMTypes.hpp>

namespace DmN::KVM {
    /// (Global Name Storage) Глобальное хранилище имён
    constinit StringStorage* GNS = new DynamicStringStorage;
    /// (Global Descriptor Storage) Глобальное хранилище дескрипторов
    constinit StringStorage* GDS = new DynamicStringStorage;
}

#endif /* DMNKVM_KVM_HPP */
