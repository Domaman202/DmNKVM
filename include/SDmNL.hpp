#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_SDMNL_HPP
#define DMN_KVM_SDMNL_HPP

#include <KVMConfig.hpp>

#include <cstdint>
#include <cstdio>

namespace DmN::SDL {
    namespace Byte {
        typedef uint8_t u1;
        typedef uint16_t u2;
        typedef uint32_t u4;

        DMN_KVM_EF u1 u1Read(FILE* file);
        DMN_KVM_EF u2 u2Read(FILE* file);
        DMN_KVM_EF u4 u4Read(FILE* file);
    }

    /// Нода
    template<typename T>
    DMN_KVM_E struct Node {
        Node(T* value, Node<T>* next) {
            this->value = value;
            this->next = next;
        }

        /// Значение ноды
        T* value;
        /// Следующая нода
        Node<T>* next;
    };

    DMN_KVM_EF unsigned int trans_two_byte(const unsigned char* bytes);
    DMN_KVM_EF unsigned int trans_three_byte(const unsigned char* bytes);
    DMN_KVM_EF unsigned int trans_six_bytes(const unsigned char* bytes);
    DMN_KVM_EF wchar_t trans_two_bytes_wchar(uint8_t byte1, uint8_t byte2);
    DMN_KVM_EF wchar_t trans_three_bytes_wchar(uint8_t byte1, uint8_t byte2, uint8_t byte3);
    DMN_KVM_EF wchar_t trans_six_bytes_wchar(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4, uint8_t byte5, uint8_t byte6);
    DMN_KVM_EF int get_utf_8_width(unsigned char byte);
}

#endif /* DMN_KVM_SDMNL_HPP */