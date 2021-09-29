#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_LLT_H
#define DMN_KVM_LLT_H

#include "KVMNameble.hpp"

namespace DmN::KVM {
    enum class LLTypes {
        UNDEFINED = 0,
        VARIABLE = 1,
        FIELD = 2,
        METHOD = 3,
        LAMBDA = 4,
        ENUM = 5,
        STRUCT = 6,
        CLASS = 7
    };

    /// (Low Level Type) Некий объект который имеет низкоуровневый тип
    struct LLT {
        explicit LLT(LLTypes llt) {
            this->llt = llt;
        }

        /// (Low Level Type) низкоуровневый тип объекта: UNDEFINED (0), VARIABLE (1), FIELD (2), METHOD (3), LAMBDA (4), ENUM (5), STRUCT (6), CLASS (7)
        LLTypes llt: 3;
    };

    /// Некий объект который имеет модификаторы
    struct Modifiable {
        explicit Modifiable(uint8_t modifier) {
            this->modifier = modifier;
        }

        /// Модификатор (PUBLIC, STATIC, INTERNAL, INTERNAL STATIC)
        uint8_t modifier: 2;
    };

    struct LLTNameble : public Nameble, public LLT {
        LLTNameble(SI_t name, LLTypes llt) : Nameble(name), LLT(llt) {}
    };
}

#endif /* DMN_KVM_LLT_H */