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

#ifdef WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#define DMN_KVM_NETWORK_CAST_TO_BUFFER(buf) (static_cast<char*>(buf))
    namespace DmN::KVM::Network {
        typedef int packet_size_t;
        typedef SOCKET socket_t;
    }
#else
#include <sys/socket.h>
#include <sys/unistd.h>
#include <arpa/inet.h>
#define DMN_KVM_NETWORK_CAST_TO_BUFFER (buf) static_cast<void*>(buf)
    namespace DmN::KVM::Network {
        typedef size_t packet_size_t;
        typedef int socket_t;
    }
#endif /* WIN32 */

#endif /* DMN_KVM_CONFIG_HPP */