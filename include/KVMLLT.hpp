#ifndef DMN_KVM_NO_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_LLT_H
#define DMN_KVM_LLT_H

namespace DmN::KVM {
    /// Хрень которая имеет низкоуровневый тип объекта
    DMN_KVM_ES(LLT) {
            explicit LLT(uint8_t llt) {
                this->llt = llt;
            }
            /// (Low Level Type) низкоуровневый тип обьякта: VARIABLE (0), FIELD (1), METHOD (2), LAMBDA (3), ENUM (4), STRUCT (5), CLASS (6)
            uint8_t llt : 3;
    };
}

#endif /* DMN_KVM_LLT_H */