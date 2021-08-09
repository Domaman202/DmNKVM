#ifndef DMN_KVM_NO_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_HEAP_HPP
#define DMN_KVM_HEAP_HPP

#include <KVMConfig.hpp>
#include <KVMESC.hpp>

#include <utility>

namespace DmN::KVM {
    /// Абстрактная куча
    DMN_KVM_ES(Heap) {
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

#endif /* DMN_KVM_HEAP_HPP */