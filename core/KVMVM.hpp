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

        void* callFunction(char* name, Value_t **args, uint8_t argc) {
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
    Байткод:
    |(0x0| Ox1 (RX), Ox2 (RY))
    MR (RX, RY) [Move Register (RX to RY)]
    |(0x1| 0x1 (TYPE), Ox2 (RX), Ox3 (RY))
    MRT (TYPE, RX, RY) [Move Register with Type (TYPE bytes, RX to RY)]
    TYPE: LL; HH; LH; HL;
    |(0x2, 0x1 (RX))
    PhS (RX) [Push to Stack (RX to stack)]
    |(0x3, 0x1 (RX))
    Pp (RX) [Pop to RX (stack to RX)]
    |(0x4, 0x1 (RX))
    Pk (RX) [Peek to RX (stack to RX)]
    |(0x5, 0x1 (RX), 0x2 (RY))
    DR (Dereference Register) [REGY = *REGX]
    |(0x6, 0x1 (RX), 0x2 (RY))
    RR (Reference Register) [REGY = (void*) REGX]
    |(0x7, 0x1 (RX), 0x2 (TYPE))
    CTV (Convert To Val) [RX = new Value_t(RX, TYPE, false))
    |(0x8, 0x1 (RX), 0x2 (TYPE))
    CTCV (Convert To Collecteble Val) [RX = new Value_t(RX, TYPE, false))
    |(0x9, 0x1 (RX))
    CFV (UnConvert Of Value) [RX = RX->value]
    |(0x10, 0x1 (RX))
    CFVADV (UnConvert Of Value And Delete Value) [RX = RX->value]
    |(0x11, 0x1 (TYPE), 0x2 (RX), 0x3 (RY), 0x4 (RZ))
    MR (Math Register) [RZ = RX TYPE RY]
    TYPE: ADD; SUB; MUL; DIV; POW; SQRT
 */