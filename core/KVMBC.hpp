#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_BC_HPP
#define DMN_KVM_BC_HPP

/// Kawaii Byte Code
namespace DmN::KVM::KBC {
    enum BC {// TODO:
        // No Operation
        NOP = 0x0,
        // Move Register
        MR = 0x1,
        // Move Register with Type (Low -> Low)
        MRT_LL = 0x2,
        // Move Register with Type (Low -> High)
        MRT_LH = 0x3,
        // Move Register with Type (High -> Low)
        MRT_HL = 0x4,
        // Move Register with Type (High -> High)
        MRT_HH = 0x5,
        // Push to Stack
        PS = 0x6,
        // Pop to register
        PP = 0x7,
        // Peek to register
        PK = 0x8,
        // Dereference Register
        DR = 0x9,
        // Reference Register
        RR = 0xA,
        // Convert To Val
        CTV = 0xB,
        // Convert To Collecteble Val
        CTCV = 0xC,
        // UnConvert Of Val
        UCOV = 0xD,
        // UnConvert Of Val and Delete val
        UCOVD = 0xE,
        // Math Register (ADD)
        MTR_ADD = 0xF,
        // Math Register (SUB)
        MTR_SUB = 0x10,
        // Math Register (MUL)
        MTR_MUL = 0x11,
        // Math Register (DIV)
        MTR_DIV = 0x12,
        // Math Register (POW)
        MTR_POW = 0x13,
        // Math Register (SQRT)
        MTR_SQRT = 0x14,
        // Load To Register (1B)
        LTR_1B = 0x15,
        // Load To Register (2B)
        LTR_2B = 0x16,
        // Load To Register (4B)
        LTR_4B = 0x17,
        // Call
        C = 0x18,
        // Call With Context
        CWC = 0x19,
        // Return
        R = 0x1A,
        // Go To
        GT = 0x1B,
        // Create Call
        CC0 = 0x1C,
        // Create Call
        CC1 = 0x1D,
        // Create Execution Context
        CEC = 0x1E,
        // Static Get Argument
        SGA = 0x1F,
        // Dynamic Get Argument
        DGA = 0x20,
        // Register String
        RS = 0x21,
        // Get String
        GS = 0x22,
        // Swap Registers
        SR = 0x23,
        // Load String
        LS = 0x24,
        // Increment References Count
        IRC = 0x25,
        // Decrement References Count
        DRC = 0x26,
        // Convert To
        CT = 0x27,
        // Convert Val To
        CVT = 0x28
    };

    enum class Primitive {
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
