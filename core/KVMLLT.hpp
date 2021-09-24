#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_LLT_H
#define DMN_KVM_LLT_H

#include "KVMNameble.hpp"

namespace DmN::KVM {
    /// (Low Level Type) Некий объект который имеет низкоуровневый тип
    struct LLT {
        explicit LLT(uint8_t llt) {
            this->llt = llt;
        }

        /// (Low Level Type) низкоуровневый тип объекта: VARIABLE (0), FIELD (1), METHOD (2), LAMBDA (3), ENUM (4), STRUCT (5), CLASS (6)
        uint8_t llt: 3;
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
        LLTNameble(SI_t name, uint8_t llt) : Nameble(name), LLT(llt) {}
    };
}

#endif /* DMN_KVM_LLT_H */