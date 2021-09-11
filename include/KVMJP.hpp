#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_JP_HPP
#define DMN_KVM_JP_HPP

#include "KVMNameble.hpp"
#include "KVMAlloc.hpp"
#include "SDmNL.hpp"
#include <cstring>
#include <tuple>

using namespace DmN::SDL::Byte;

namespace DmN::KVM::JP {
    DMN_KVM_E struct ConstantPool {
        u1 tag = 0;
        union {
            SI_t SID = 0; // String ID (Строка, Enum/Структура/Класс, Дескриптор, Имя)
            CI_t CID = 0; // Class ID (ID класса)
            struct {
                SI_t NID = 0; // Name ID (Имя)
                CI_t CID = 0; // Class ID (ID класса)
            } FMI; // Field, MethodRef, InterfaceMethodRef
            // Циферки xD
            int8_t int8 = 0;
            uint8_t uint8 = 0;
            int16_t int16 = 0;
            uint16_t uint16 = 0;
            int32_t int32 = 0;
            uint32_t uint32 = 0;
            int64_t int64 = 0;
            uint64_t uint64 = 0;
            float float_ = 0f;
            double double_ = .0;
        };
    };

    char* readString(FILE* file);

    std::tuple<u2, ConstantPool*[], SS*> readConstantPool(FILE* file);
}

#endif /* DMN_KVM_JP_HPP */