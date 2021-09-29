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
                        regs->rs[++(*i)] = regs->rs[++(*i)];
                        break;
                    case C::MRT_LL:
                        ((SDL::byte_map_2b_32b*) regs->rs[++(*i)])->b0 = ((SDL::byte_map_2b_32b*) regs->rs[++(*i)])->b0;
                        break;
                    case C::MRT_LH:
                        ((SDL::byte_map_2b_32b*) regs->rs[++(*i)])->b0 = ((SDL::byte_map_2b_32b*) regs->rs[++(*i)])->b1;
                        break;
                    case C::MRT_HL:
                        ((SDL::byte_map_2b_32b*) regs->rs[++(*i)])->b1 = ((SDL::byte_map_2b_32b*) regs->rs[++(*i)])->b0;
                        break;
                    case C::MRT_HH:
                        ((SDL::byte_map_2b_32b*) regs->rs[++(*i)])->b1 = ((SDL::byte_map_2b_32b*) regs->rs[++(*i)])->b1;
                        break;
                    case C::PS:
                        stack->push(regs->rs[++(*i)]);
                        break;
                    case C::PP:
                        regs->rs[++(*i)] = stack->peekPop();
                        break;
                    case C::PK:
                        regs->rs[++(*i)] = stack->peek();
                        break;
                    case C::DR:
                        regs->rs[++(*i)] = *(void**) regs->rs[++(*i)];
                        break;
                    case C::RR:
                        regs->rs[++(*i)] = (void**) regs->rs[++(*i)];
                        break;
                    case C::CTV: {
                        uint8_t reg = ++(*i);
                        regs->rs[reg] = new Value_t(regs->rs[reg], ++(*i), false);
                        break;
                    }
                    case C::CTCV: {
                        uint8_t reg = ++(*i);
                        regs->rs[reg] = new Value_t(regs->rs[reg], ++(*i), true);
                        break;
                    }
                    case C::UCOV: {
                        uint8_t reg = ++(*i);
                        regs->rs[reg] = ((Value_t*) regs->rs[reg])->value;
                        break;
                    }
                    case C::UCOVD: {
                        uint8_t reg = ++(*i);
                        auto* val = ((Value_t*) regs->rs[reg]);
                        regs->rs[reg] = val->value;
                        delete val;
                        break;
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
    };
}

#endif /* DMN_KVM_VM_HPP */