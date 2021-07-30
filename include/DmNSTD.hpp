#pragma once
#ifndef DMNKVM_DMNSTD_HPP
#define DMNKVM_DMNSTD_HPP

#include <cstdint>
#include "KVMConfig.hpp"

namespace DmN::std {
    /// Нода
    template<typename T>
    exStruct(Node) {
        Node(T* value, Node<T>* next) {
            this->value = value;
            this->next = next;
        }

        /// Значение ноды
        T* value;
        /// Следующая нода
        Node<T>* next;
    };

    unsigned int trans_two_byte(const unsigned char* bytes);
    unsigned int trans_three_byte(const unsigned char* bytes);
    unsigned int trans_six_bytes(const unsigned char* bytes);
    wchar_t trans_two_bytes_wchar(uint8_t byte1, uint8_t byte2);
    wchar_t trans_three_bytes_wchar(uint8_t byte1, uint8_t byte2, uint8_t byte3);
    wchar_t trans_six_bytes_wchar(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4, uint8_t byte5, uint8_t byte6);
    int get_utf_8_width(unsigned char byte);
}

#endif /* DMNKVM_DMNSTD_HPP */