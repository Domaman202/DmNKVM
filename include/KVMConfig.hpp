#ifndef DMN_KVM_NO_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA*/
#ifndef DMNKVM_KVMCONFIG_HPP
#define DMNKVM_KVMCONFIG_HPP

#include <DmNPlatformConfig.h>

#include <cstdint>

#ifndef DMN_KVM_CUSTOM_CONFIG
#define DMN_KVM_USE_GLOBAL_NAME_STORAGES
#endif /* DMN_KVM_CUSTOM_CONFIG*/

#ifndef DMN_KVM_USE_CUSTOM_SIZE_CONFIG

namespace DmN::KVM {
#ifdef DMN_KVM_USE_8BIT_NAME_ID
    typedef uint8_t SI_t;
#elif DMN_KVM_USE_16BIT_NAME_ID
    typedef uint16_t SI_t;
#else
    typedef uint32_t SI_t;
#endif /* DMN_KVM_USE_8BIT_NAME_ID */
}

namespace DmN::KVM {
#ifdef DMN_KVM_USE_8BIT_CLASS_ID
    typedef uint8_t CI_t;
#elif DMN_KVM_USE_16BIT_CLASS_ID
    typedef uint16_t CI_t;
#else
    typedef uint32_t CI_t;
#endif /* DMN_KVM_USE_8BIT_CLASS_ID */
}

namespace DmN::KVM {
#ifdef DMN_KVM_USE_8BIT_NAMESPACE_ID
    typedef uint8_t NSI_t;
#elif DMN_KVM_USE_16BIT_NAMESPACE_ID
    typedef uint16_t NSI_t;
#else
    typedef uint32_t NSI_t;
#endif /* DMN_KVM_USE_8BIT_NAMESPACE_ID */
}

#endif /* DMN_KVM_USE_CUSTOM_SIZE_CONFIG */

#endif /* DMNKVM_KVMCONFIG_HPP */