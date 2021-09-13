#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_CONSTRUCTORS_HPP
#define DMN_KVM_CONSTRUCTORS_HPP

#include "KVMError.hpp"
#include "KVMESC.hpp"

using namespace DmN::KVM::Error;

namespace DmN::KVM::Utils {
    /*!
     * Пытается собрать объект
     * @param obj объект для сборки
     * @return возвращает значение из DmN::KVM::ERROR::CR
    */
    DMN_KVM_EF CR
    tryCollect(GCObject
               *obj);

    /*!
     * Насильно собирает объект
     * @param obj объект для сборки
     */
    DMN_KVM_EF inline void collect(GCObject *obj);
}

#endif /* DMN_KVM_CONSTRUCTORS_HPP */