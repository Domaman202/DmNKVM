#pragma once
#ifndef DMNKVM_KVMCONFIG_HPP
#define DMNKVM_KVMCONFIG_HPP

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

#ifdef USE_WIN32_EXPORT
#define export __declspec(dllexport)
#define exEnum(name) enum export name
#define exStruct(name) struct export name
#define exClass(name) class export name
#elif USE_LINUX_EXPORT
// TODO: NEED TO REALISE
#elif USE_MAC_EXPORT
// TODO: NEED TO REALISE
#else
#define export
#define exEnum(name) enum name
#define exStruct(name) struct name
#define exClass(name) class name
#endif /* USE_WIN32_EXPORT */

#endif /* DMNKVM_KVMCONFIG_HPP */