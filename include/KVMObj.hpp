#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_OBJ_HPP
#define DMN_KVM_OBJ_HPP

#include "KVMESC.hpp"

namespace DmN::KVM {
    DMN_KVM_E struct Instanceble { // TODO: NEED TO REALIZE
        virtual struct Object_t *newInstance() = 0;
    };

    DMN_KVM_E struct Object_t { // TODO: NEED TO REALIZE
        Instanceble *type;
    };
}

#endif /* DMN_KVM_OBJ_HPP */
