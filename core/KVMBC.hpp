#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_BC_HPP
#define DMN_KVM_BC_HPP

/// Kawaii Byte Code
namespace DmN::KVM::KBC {
    enum BC {// TODO:
        /// No Operation
        NOP = 0x0,

        /* REGISTER */

        /*!
         * Move Register
         * Копирует указатель регистра RA в регистр RB
         * (RA,RB)
         * [RA & RB - номера регистров]
         */
        MR,

        /*!
         * Move Register with Type ((A + X) -> (B + Y), (S)) [ X & Y - Offset, A & B - Regs, S - Size ]
         * Перемещает S байт из регистра RA в регистр RB  со смещением указателя для RA в X и смещением указателя для RB в Y
         * (RA, X, RB, Y, S)
         * [RA & RB - номера регистров ; X & Y - смещение; S - кол-во байт для перемещения]
         */
        MRT,

        /*!
         * Swap Register
         * Меняет указатели RA и RB местами
         * [RA & RB - номера регистров]
         */
        SR,

        /*!
         * Load Clean Value
         * Загружает сырое значение в регистр R
         * (T, B.., R)
         * [T - тип значения (#Primitive) (INT8, INT16, INT32, INT64) ; B.. - байты ; R -регистр)
         */
        LCV,

        /*!
         * Load Parsed Value
         * Загружает обработанное значение в регистр R
         * (T, B.., R)
         * [T - тип значения (#Primitive) (INT8, INT16, INT32, INT64) ; B.. - байты ; R -регистр)
         */
        LPV,

        /*!
         * Load UnParsed Value
         * Загружает распаршенное значение
         * (RA, RB)
         * [RA - регистр с исходным значением ; RB - регистр с распаршенным значением]
         */
        LUPV,

        /*!
         * Clear Register
         * Обнуляет указатель регистра
         * (R)
         * [R - регистр]
         */
        CR,

        /* STACK */

        /*!
         * Copy Stack Value
         */
        CSV,

        /*!
         * Swap Stack
         * Меняет местами 2 верхних элемента стека
         */
        SS,

        /*!
         * Push Clean Value
         * Загружает сырое значение в стек
         * (T, B..)
         * [T - тип значения (#Primitive) (INT8, INT16, INT32, INT64) ; B.. - байты)
         */
        PCV,

        /*!
         * Push Parsed Value
         * Загружает обработанное значение в стек
         * (T, B..)
         * [T - тип значения (#Primitive) (INT8, INT16, INT32, INT64) ; B.. - байты)
         */
        PPV,

        /// Push UnParsed Value
        PUPV,

        /*!
         * Pop Value
         * Удаляет верхний элемент стека
         */
        PV,

        /*!
         * Clear Stack
         * Чистит стек
         */
        CS,

        /* STACK / REGISTER */

        /*!
         * Load To Stack
         * Загружает указатель регистра R в стек
         * (R)
         * [R - регистр]
         */
        LTS,

        /*!
         * Load From Stack
         * Загружает указатель значения из стека в регистр R
         * (R)
         * [R - регистр]
         */
        LFS,

        /* MATH REGISTER */

        /// Add (T + T) [ T - #Primitive ]
        ADD,

        /// Subtract (T - T) [ T - #Primitive ]
        SUB,

        /// Multiply (T * T) [ T - #Primitive ]
        MUL,

        /// Divide (T / T) [ T - #Primitive ]
        DIV,

        /* Call */

        /*!
         * Call Global Heap
         * Получает функцию по дескриптору (SI_t) который он получает из регистра R и вызывает её
         * (R)
         * [R - регистр]
         */
        CGH,

        /* Struct Utils */

        /*!
         * Push New String
         * Получает последний элемент стека (нашу строку) и создаёт ей id-шник (SI_t) который помещает в стак
         */
        PNS,

        /*!
         * Create New String
         * Собирает строку из стека возвращает её id-шник (SI_t) который помещает в стак
         */
        CNS,

        /* PTR UTILS */

        /*!
         * Alloc Ref
         * Выделяет память в регистр RA с размером заданным в регистре RB
         * (RA, RB)
         * [RA - регистр для хранения указателя ; RB - регистр с кол-вом байт для выделения]
         */
        AR,

        /*!
         * Alloc Const Ref
         * Выделяет память заданную размером в 2х байтах константы BYTES в регистр R
         * (R, BYTES)
         * [R - регистр хранящий указатель ; BYTES (2) - кол-во байт для выделения)
         */
        ACR,

        /*!
         * Free Ref
         * Высвобождает память из регистра R и зануляет его указатель
         * (R)
         * [R - регистр с указателем]
         */
        FR,

        /*!
         * Alloc Stack Ref
         * Выделяет стековую память в регистр RA с размером заданным в регистре RB
         * (RA, RB)
         * [RA - регистр для хранения указателя ; RB - регистр с кол-вом байт для выделения]
         */
        ASR,

        /*!
         * Alloc Stack Const Ref
         * Выделяет стековую память заданную размером в 2х байтах константы BYTES в регистр R
         * (R, BYTES)
         * [R - регистр хранящий указатель ; BYTES (2) - кол-во байт для выделения)
         */
        ASCR,

        /*!
         * Box Ref
         * Упаковывает ссылку RA и помещает её в RB
         * (RA, RB)
         * [RA - регистр регистр исходной ссылки ; RB - (выход) с запакованной ссылкой]
         */
        BR,

        /*!
         * UnBox Ref
         * Распаковывает ссылку RA и помещает её в RB
         * (RA, RB)
         * [RA - регистр с запакованной ссылкой ; RB - (выход) регистр исходной ссылки]
         */
        UBR,

        /*!
         * Get Array Element
         */
        GAE,

        /// Set Element To Array
        SETA,

        /// Get Ptr Of Array Element
        GPOAE,

        /* CODE COUNTER FEATURES */

        /// Set Code Counter
        SCC,

        /// Get Code Counter
        GCC,

        /// Jump With Offset
        JWO
    };

    enum Primitive {
        INT8 = 0,
        UINT8 = 1,
        INT16 = 2,
        UINT16 = 3,
        INT32 = 4,
        UINT32 = 5,
        INT64 = 6,
        UINT64 = 7,
        FLOAT = 8,
        DOUBLE = 9,
        REFERENCE = 10
    };
}

#endif /* DMN_KVM_BC_HPP */
