#ifndef DMN_KVM_NO_USE_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMN_KVM_VM_HPP
#define DMN_KVM_VM_HPP

#include "KVMProcess.hpp"
#include "KVMTypes.hpp"
#include "KVMCall.hpp"
#include "KVMESC.hpp"
#include "KVMSR.hpp"

namespace DmN::KVM::VM {
    /// Контекст выполнения
    struct ExecuteContext {
        /// Текущий вызов
        Call *lastCall;
        /// Текущий процесс
        Process *lastProcess;
        /// Текущий указатель кода
        size_t lastBcPtr;
        /// Предыдущий вызов
        ExecuteContext *prevContext;
    };

    /// Виртуальная машина A класса
    class VMCA {
    public:
        ExecuteContext *mainContext;
        BCMethod_t *main = (BCMethod_t*) malloc(sizeof(BCMethod_t));;

        VMCA(uint8_t *code, size_t cs, Value_t** args, uint8_t argc) {
            SS* mainSS = new DSS();
            Heap* mainHeap = new DHeap();
            mainContext = new ExecuteContext{
                    .lastCall = nullptr,
                    .lastProcess = new Process{
                            .threads = new Thread *[]{
                                    new Thread{
                                            .cs = new Stack<Call *>(new SDL::Node(new Call{
                                                .obj_caller = nullptr,
                                                .method_caller = nullptr,
                                                .obj = nullptr,
                                                .method = main,
                                                .args = args,
                                                .argc = argc
                                            })),
                                            .stack = new Stack<void *>(nullptr),
                                            .regs = new Resisters(code[0] | (code[1] << 8)),
                                    }
                            },
                            .tc = 1,
                            .heap = mainHeap,
                            .strings = mainSS
                    },
                    .lastBcPtr = 2
            };
            createMain(main, mainSS, code, cs);
        }

        void* callMain() {
            // TODO:
        }

        static void createMain(BCMethod_t *ptr, SS* ss, uint8_t *code, size_t cs) {
            new (ptr) BCMethod_t(ss->add("$main()V"), code, cs);
        }
    };
}

#endif /* DMN_KVM_VM_HPP */

/*
    Разметка кода:
    0x0 - 0x10 Кол-во регистров главного потока
    0x10 - 0xXXX Код
 */
/*
    Байт код:
    |0x0| Ox1 (RX), Ox2 (RY)
    MR (RX, RY)
    Move Register
    [RX to RY]

    |0x1 - 0x4| Ox1 (RX), Ox2 (RY)
    MRT (RX, RY)
    Move Register with Type
    [(LL,HH,LH,HL) bytes, RX to RY]

    |0x5| 0x1 (RX)
    PhS (RX)
    Push to Stack
    [RX to stack]

    |0x6| 0x1 (RX)
    Pp (RX)
    Pop to RX
    [Stack to RX]

    |0x7| 0x1 (RX)
    Pk (RX)
    Peek to RX
    [Stack to RX]

    |0x8| 0x1 (RX), 0x2 (RY)
    DR (RX, RY)
    Dereference Register
    [REGY = *REGX]

    |0x9| 0x1 (RX), 0x2 (RY)
    RR (RX, RY)
    Reference Register
    [REGY = (void*) REGX]

    |0xA| 0x1 (RX), 0x2 (TYPE)
    CTV (RX, TYPE)
    Convert To Val
    [RX = new Value_t(RX, TYPE, false)]

    |0xB| 0x1 (RX), 0x2 (TYPE)
    CTCV (RX, TYPE)
    Convert To Collecteble Val
    [RX = new Value_t(RX, TYPE, false)]

    |0xC| 0x1 (RX)
    CFV (RX)
    UnConvert Of Value
    [RX = RX->value]

    |0xD| 0x1 (RX)
    CFVADV (RX)
    UnConvert Of Value And Delete Value
    [RX = RX->value]

    |0xF - 0x15| 0x1 (RX), 0x2 (RY), 0x3 (RZ)
    MR (RX, RY, RZ)
    Math Register
    [RZ = RX TYPE (TYPE: ADD; SUB; MUL; DIV; POW; SQRT) RY]

    |0x16| 0x1 (RX), 0x2 (BYTE)
    LTR1 (RX, BYTE)
    Load To Register
    [RX = BYTE]

    |0x17| 0x1 (RX), 0x2 (BYTE0), 0x3 (BYTE1)
    LTR2 (RX, BYTE0, BYTE1)
    Load To Register
    [RX = BYTE0 | (BYTE1 << 8)]

    |0x18| 0x1 (RX), 0x2 (BYTE0), 0x3 (BYTE1), 0x4 (BYTE2), 0x5(BYTE3))
    LTR4 (RX, BYTE0, BYTE1, BYTE2, BYTE3)
    Load To Register
    [RX = BYTE0 | (BYTE1 << 8) | BYTE2 << 16) | (BYTE3 << 24)]
 */