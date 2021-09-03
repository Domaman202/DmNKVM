#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_JP_HPP
#define DMN_KVM_JP_HPP

#include "KVMConfig.hpp"
#include "SDmNL.hpp"

using namespace DmN::SDL::Byte;

namespace DmN::KVM::JP {
    DMN_KVM_E struct ConstantPool {
        u1 tag = 0;
        union {
            SI_t SID; // String ID (Строка, Enum/Структура/Класс, Дескриптор, Имя)
            CI_t CID; // Class ID (ID класса)
            struct {
                SI_t NID; // Name ID (Имя)
                CI_t CID; // Class ID (ID класса)
            } FMI; // Field, MethodRef, InterfaceMethodRef
            // Циферки xD
            int8_t int8;
            uint8_t uint8;
            int16_t int16;
            uint16_t uint16;
            int32_t int32;
            uint32_t uint32;
            float float_;
            double double_;
        };
    };
}

#endif /* DMN_KVM_JP_HPP */