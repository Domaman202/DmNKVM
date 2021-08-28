#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_CONFIG_HPP
#define DMN_KVM_CONFIG_HPP

#include <DmNPlatformConfig.h>
#include <cstdint>

#ifdef DMN_KVM_UNSAFE
#define DMN_KVM_NO_CHECK_NULLPTR
#endif /* DMN_KVM_UNSAFE */

#ifndef DMN_KVM_USE_CUSTOM_SIZE_CONFIG

namespace DmN::KVM {
#ifdef DMN_KVM_USE_8BIT_NAME_ID
    using SI_t = uint8_t;
#elif DMN_KVM_USE_16BIT_NAME_ID
    using SI_t = uint16_t;
#else
    using SI_t = uint32_t;
#endif /* DMN_KVM_USE_8BIT_NAME_ID */
}

namespace DmN::KVM {
#ifdef DMN_KVM_USE_8BIT_CLASS_ID
    using CI_t = uint8_t;
#elif DMN_KVM_USE_16BIT_CLASS_ID
    using CI_t = uint16_t;
#else
    using CI_t = uint32_t;
#endif /* DMN_KVM_USE_8BIT_CLASS_ID */
}

namespace DmN::KVM {
#ifdef DMN_KVM_USE_8BIT_NAMESPACE_ID
    using NSI_t = uint8_t;
#elif DMN_KVM_USE_16BIT_NAMESPACE_ID
    using NSI_t = uint16_t;
#else
    using NSI_t = uint32_t;
#endif /* DMN_KVM_USE_8BIT_NAMESPACE_ID */
}

#endif /* DMN_KVM_USE_CUSTOM_SIZE_CONFIG */

#endif /* DMN_KVM_CONFIG_HPP */