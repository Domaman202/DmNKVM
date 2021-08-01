#pragma once
#ifndef DMNKVM_KVMHEAP_HPP
#define DMNKVM_KVMHEAP_HPP

#include <KVMConfig.hpp>
#include <KVMESC.hpp>

#include <utility>

namespace DmN::KVM {
    /// Абстрактная куча
    eStruct(Heap) {
            virtual CI_t addNew(ClassBase* clazz) = 0;
            virtual CI_t add(ClassBase* clazz) = 0;
            virtual void replace(ClassBase* clazz, CI_t id) = 0;
            virtual void remove(ClassBase* clazz) = 0;
            virtual void remove(CI_t id) = 0;
            virtual CI_t get(ClassBase* clazz) = 0;
            virtual ClassBase* get(CI_t id) = 0;
            //
            virtual SDL::pair<ClassBase**, size_t> getParents(ClassBase* clazz) = 0;
            virtual SDL::pair<ClassBase**, size_t> getParents(CI_t clazz) = 0;
    };
}

#endif /* DMNKVM_KVMHEAP_HPP */