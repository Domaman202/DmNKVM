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

        VMCA(uint8_t *code, size_t cs, Value_t** args, size_t argc) {
            SS* mainSS = new DSS();
            Heap* mainHeap = nullptr; // TODO: !WIP!
            mainContext = new ExecuteContext{
                    .lastCall = nullptr,
                    .lastProcess = new Process{
                            .threads = new Thread *[]{
                                    new Thread{
                                            .cs = new Stack<Call *>(new SDL::Node(new Call{
                                                .obj_caller = nullptr,
                                                .method_caller = nullptr,
                                                .obj = nullptr,
                                                .method = main
                                            })),
                                            .stack = new Stack<void *>(nullptr),
                                            .regs = new Resisters(code[0] | (code[1] << 8)),
                                    }
                            },
                            .tc = 1,
                            .heap = mainHeap,
                            .strings = mainSS
                    }
            };
            createMain(main, mainSS, code, cs);
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

 */