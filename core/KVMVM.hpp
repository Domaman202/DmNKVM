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

namespace DmN::KVM {
    /// Контекст выполнения
    struct ExecuteContext {
        /// Текущий вызов
        Call *call;
        /// Текущий поток
        Thread* thread;
        /// Текущий процесс
        Process *process;
        /// Текущий указатель кода
        size_t bcPtr;
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

        void* eval(ExecuteContext c, const uint8_t* b, size_t cs) {
            for (size_t* i = &c.lastBcPtr; *i < cs; (*i)++) {
                switch (b[*i]) {
                    // TODO:
                }
            }
        }

        static void createMain(BCMethod_t *ptr, SS* ss, uint8_t *code, size_t cs) {
            new (ptr) BCMethod_t(ss->add("$main()V"), code, cs);
        }

        static void call(VMCA* vm, ExecuteContext* context) {
            Stack<void*>* stack = thread->stack;
            stack->push(vm);
            stack->push(context);

            auto* method = context->call->method;
            if (typeid(*method) == typeid(BCMethod_t)) {
                auto method = (BCMethod_t*) context->call->method;
                vm->eval(context, method->bc, method->cs);
            } else if (typeid(*method) == typeid(NMethod_t)) {
                auto method = ((NMethod_t*) context->call->method);
                method->call(new void*[] { c, b, cs }, 3);
            }
        }
    };
}

#endif /* DMN_KVM_VM_HPP */