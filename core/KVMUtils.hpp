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
     * Насильно собирает объект
     * @param obj объект для сборки
     */
    inline void collect(GCObject *obj) {
        delete obj;
    }

    /*!
     * Пытается собрать объект
     * @param obj объект для сборки
     * @return возвращает значение из DmN::KVM::ERROR::CR
    */
    CR tryCollect(GCObject *obj) {
        if (obj->isCollectable) {
            if (obj->references == 0) {
                collect(obj);
                return static_cast<CR>(BaseError::SUCCESS);
            }
            return CR::OBJECT_REFERENCE_NOT_NULL;
        }
        return CR::OBJECT_NO_COLLECTABLE;
    }
}

#endif /* DMN_KVM_CONSTRUCTORS_HPP */