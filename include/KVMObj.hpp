#ifndef DMN_KVM_NO_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA*/
#ifndef DMNKVM_KVMOBJ_HPP
#define DMNKVM_KVMOBJ_HPP

#include <KVMConfig.hpp>
#include "KVMESC.hpp"

namespace DmN::KVM {
    DMN_KVM_ES(Object) { // TODO: NEED TO REALIZE
        Instanceble* type;
    };
}

#endif /* DMNKVM_KVMOBJ_HPP */
