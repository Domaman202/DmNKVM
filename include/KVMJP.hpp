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
using namespace DmN::SDL::Pairs;

namespace DmN::KVM::JP {
    /// Пул констант
    DMN_KVM_E struct ConstantPool {
        u1 tag = 0;
        union {
            SI_t SID; // String ID (Строка, Enum/Структура/Класс, Дескриптор, Имя)
            CI_t CID; // Class ID (ID класса)
            struct {
                SI_t NID = 0; // Name ID (Имя)
                CI_t CID = 0; // Class ID (ID класса)
            } FMI; // Field, MethodRef, InterfaceMethodRef
            // Циферки xD
            int8_t int8;
            uint8_t uint8;
            int16_t int16;
            uint16_t uint16;
            int32_t int32 = 0; /* Default Value */
            uint32_t uint32;
            int64_t int64;
            uint64_t uint64;
            float float_;
            double double_;
        };
    };

    /*!
     * Читает весь файл в одну строку
     * @param file файл который нужно считать
     * @return Итоговая строка
     */
    char *readString(FILE *file);

    Triple<u2, ConstantPool **, SS *> readConstantPool(FILE *file);
}

#endif /* DMN_KVM_JP_HPP */