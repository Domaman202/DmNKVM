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
#include "KVMBC.hpp"
#include <typeinfo.h>

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
                    .call = nullptr,
                    .process = new Process{
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
                    .bcPtr = 2
            };
            createMain(main, mainSS, code, cs);
        }

        void* callMain() {
            // TODO:
        }

        void* eval(ExecuteContext* c, const uint8_t* b, size_t cs) {
            auto thread = c->thread;
            auto regs = thread->regs;
            auto stack = thread->stack;

            for (size_t* i = &c->bcPtr; *i < cs; (*i)++) {
                using C = DmN::KVM::KBC::BC;
                switch (b[*i]) {// TODO:
                    case C::NOP:
                        break;
                    case C::MR:
                        regs->rs[RNV(i, b)] = regs->rs[RNV(i, b)];
                        break;
                    case C::MRT_LL:
                        ((SDL::byte_map_2b_32b*) regs->rs[RNV(i, b)])->b0 = ((SDL::byte_map_2b_32b*) regs->rs[RNV(i, b)])->b0;
                        break;
                    case C::MRT_LH:
                        ((SDL::byte_map_2b_32b*) regs->rs[RNV(i, b)])->b0 = ((SDL::byte_map_2b_32b*) regs->rs[RNV(i, b)])->b1;
                        break;
                    case C::MRT_HL:
                        ((SDL::byte_map_2b_32b*) regs->rs[RNV(i, b)])->b1 = ((SDL::byte_map_2b_32b*) regs->rs[RNV(i, b)])->b0;
                        break;
                    case C::MRT_HH:
                        ((SDL::byte_map_2b_32b*) regs->rs[RNV(i, b)])->b1 = ((SDL::byte_map_2b_32b*) regs->rs[RNV(i, b)])->b1;
                        break;
                    case C::PS:
                        stack->push(regs->rs[RNV(i, b)]);
                        break;
                    case C::PP:
                        regs->rs[RNV(i, b)] = stack->peekPop();
                        break;
                    case C::PK:
                        regs->rs[RNV(i, b)] = stack->peek();
                        break;
                    case C::DR: {
                        auto reg = RNV(i, b);
                        regs->rs[reg] = *(void **) regs->rs[reg];
                        break;
                    }
                    case C::RR: {
                        auto reg = RNV(i, b);
                        regs->rs[reg] = (void **) regs->rs[reg];
                        break;
                    }
                    case C::CTV: {
                        uint8_t reg = RNV(i, b);
                        regs->rs[reg] = new Value_t(regs->rs[reg], RNV(i, b), false);
                        break;
                    }
                    case C::CTCV: {
                        uint8_t reg = RNV(i, b);
                        regs->rs[reg] = new Value_t(regs->rs[reg], RNV(i, b), true);
                        break;
                    }
                    case C::UCOV: {
                        uint8_t reg = RNV(i, b);
                        regs->rs[reg] = ((Value_t*) regs->rs[reg])->value;
                        break;
                    }
                    case C::UCOVD: {
                        uint8_t reg = RNV(i, b);
                        auto* val = ((Value_t*) regs->rs[reg]);
                        regs->rs[reg] = val->value;
                        delete val;
                        break;
                    }
                    case C::MTR_ADD: {
                        auto rX = regs->rs[RNV(i, b)];
                        auto rY = regs->rs[RNV(i, b)];
                        auto rZ = regs->rs[RNV(i, b)];
//                        switch(++(*i)) {
//                            case VTypes::UNDEFINED:
//                        }
                    }
                }
            }
        }

        static void createMain(BCMethod_t *ptr, SS* ss, uint8_t *code, size_t cs) {
            new (ptr) BCMethod_t(ss->add("$main()V"), code, cs);
        }

        static void call(VMCA* vm, ExecuteContext* context) {
            auto method = context->call->method;
            if (typeid(*method) == typeid(BCMethod_t)) {
                Stack<void*>* stack = context->thread->stack;
                stack->push(vm);
                stack->push(context);
                auto m = (BCMethod_t*) method;
                vm->eval(context, m->bc, m->cs);
            } else if (typeid(*method) == typeid(NMethod_t)) {
                ((NMethod_t*) method)->call(new void*[] { vm, context }, 2);
            } else
                ((NRMethod_t*) method)->ref(new void*[] { vm, context }, 2);
        }

        static inline uint8_t RNV(size_t* i, const uint8_t* bytes) {
            return bytes[++(*i)];
        }
    };
}

#endif /* DMN_KVM_VM_HPP */