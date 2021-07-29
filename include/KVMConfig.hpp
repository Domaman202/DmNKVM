#pragma once
#ifndef DMNKVM_KVMCONFIG_HPP
#define DMNKVM_KVMCONFIG_HPP

#include <cstdint>

#ifndef DMN_KVM_CUSTOM_CONFIG
//
#define DMN_KVM_USE_GLOBAL_NAME_STORAGES
//
#endif

#ifndef DMN_KVM_USE_CUSTOM_SIZE_CONFIG
//
namespace DmN::KVM {
    //
#ifdef DMN_KVM_USE_8BIT_NAME_ID
    typedef uint8_t SI_t;
#elseif DMN_KVM_USE_16BIT_NAME_ID
    typedef uint16_t SI_t;
#else
    typedef uint32_t SI_t;
#endif
    //
#ifdef DMN_KVM_USE_8BIT_CLASS_ID
    typedef uint8_t CI_t;
#elseif DMN_KVM_USE_16BIT_CLASS_ID
    typedef uint16_t CI_t;
#else
    typedef uint32_t CI_t;
#endif
    //
}
//
#endif

#endif /* DMNKVM_KVMCONFIG_HPP */