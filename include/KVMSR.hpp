#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_SR_HPP
#define DMN_KVM_SR_HPP

#include "KVMConfig.hpp"
#include "SDmNL.hpp"

namespace DmN::KVM {
    template<typename T>
    DMN_KVM_E struct Stack {
    protected:
        /// Стартовая нода
        DmN::SDL::Node<T> node;
    public:
        // TODO:
    };

    DMN_KVM_E struct Resisters {
        // TODO:
    };
}

#endif /* DMN_KVM_SR_HPP */