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
        //
        Value_t* cUndefined = new Value_t(nullptr, (uint8_t) VTypes::UNDEFINED, true);
        Value_t* cNaN = new Value_t(nullptr, (uint8_t) VTypes::NaN, true);
        Value_t* cInf = new Value_t(nullptr, (uint8_t) VTypes::INF, true);
        Value_t* cNInf = new Value_t(this, (uint8_t) VTypes::INF, true);

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

            for (size_t *i = &c->bcPtr; *i < cs; (*i)++) {
                using C = DmN::KVM::KBC::BC;
                switch (b[*i]) {// TODO:
                    case C::NOP:
                        break;
                    case C::MR:
                        regs->rs[RNV(i, b)] = regs->rs[RNV(i, b)];
                        break;
                    case C::MRT_LL:
                        ((SDL::byte_map_2b_32b *) regs->rs[RNV(i, b)])->b0 = ((SDL::byte_map_2b_32b *) regs->rs[RNV(i,
                                                                                                                    b)])->b0;
                        break;
                    case C::MRT_LH:
                        ((SDL::byte_map_2b_32b *) regs->rs[RNV(i, b)])->b0 = ((SDL::byte_map_2b_32b *) regs->rs[RNV(i,
                                                                                                                    b)])->b1;
                        break;
                    case C::MRT_HL:
                        ((SDL::byte_map_2b_32b *) regs->rs[RNV(i, b)])->b1 = ((SDL::byte_map_2b_32b *) regs->rs[RNV(i,
                                                                                                                    b)])->b0;
                        break;
                    case C::MRT_HH:
                        ((SDL::byte_map_2b_32b *) regs->rs[RNV(i, b)])->b1 = ((SDL::byte_map_2b_32b *) regs->rs[RNV(i,
                                                                                                                    b)])->b1;
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
                        regs->rs[reg] = ((Value_t *) regs->rs[reg])->value;
                        break;
                    }
                    case C::UCOVD: {
                        uint8_t reg = RNV(i, b);
                        auto *val = ((Value_t *) regs->rs[reg]);
                        regs->rs[reg] = val->value;
                        delete val;
                        break;
                    }
                    case C::MTR_ADD: {
                        auto rX = regs->rs[RNV(i, b)];
                        auto rY = regs->rs[RNV(i, b)];
                        auto rZ = RNV(i, b);
                        switch (*(VTypes *) regs->rs[RNV(i, b)]) {
                            case VTypes::UNDEFINED:
                                regs->rs[rZ] = cUndefined;
                                break;
                            case VTypes::NaN:
                                regs->rs[rZ] = cNaN;
                                break;
                            case VTypes::INF:
                                regs->rs[rZ] = cNInf;
                                break;
                            case VTypes::INT8:
                                regs->rs[rZ] = new int8_t(*(int8_t *) rX + *(int8_t *) rY);
                                break;
                            case VTypes::INT16:
                                regs->rs[rZ] = new int16_t(*(int16_t *) rX + *(int16_t *) rY);
                                break;
                            case VTypes::INT32:
                                regs->rs[rZ] = new int32_t(*(int32_t *) rX + *(int32_t *) rY);
                                break;
                            case VTypes::INT64:
                                regs->rs[rZ] = new int64_t(*(int64_t *) rX + *(int64_t *) rY);
                                break;
                            case VTypes::UINT8:
                                regs->rs[rZ] = new uint8_t(*(uint8_t *) rX + *(uint8_t *) rY);
                                break;
                            case VTypes::UINT16:
                                regs->rs[rZ] = new uint16_t(*(uint16_t *) rX + *(uint16_t *) rY);
                                break;
                            case VTypes::UINT32:
                                regs->rs[rZ] = new uint32_t(*(uint32_t *) rX + *(uint32_t *) rY);
                                break;
                            case VTypes::UINT64:
                                regs->rs[rZ] = new uint64_t(*(uint64_t *) rX + *(uint64_t *) rY);
                                break;
                            case VTypes::FLOAT:
                                regs->rs[rZ] = new float(*(float *) rX + *(float *) rY);
                                break;
                            case VTypes::DOUBLE:
                                regs->rs[rZ] = new double(*(double *) rX + *(double *) rY);
                                break;
                            case VTypes::CHAR:
                                regs->rs[rZ] = new char(*(char *) rX + *(char *) rY);
                                break;
                            case VTypes::REFERENCE:
                                regs->rs[rZ] = reinterpret_cast<void*>(reinterpret_cast<intptr_t>(rX) + reinterpret_cast<intptr_t>(rY));
                                break;
                            case VTypes::OBJECT:
                                // TODO:
                                break;
                        }
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