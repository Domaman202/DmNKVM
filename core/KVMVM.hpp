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
#include <cmath>

namespace DmN::KVM {
    /// Контекст выполнения
    struct ExecuteContext {
        /// Текущий вызов
        Call *call;
        /// Текущий поток
        Thread *thread;
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
        BCMethod_t *main = (BCMethod_t *) malloc(sizeof(BCMethod_t));;
        //
        Value_t *cUndefined = new Value_t(nullptr, (uint8_t) VTypes::UNDEFINED, true);
        Value_t *cNaN = new Value_t(nullptr, (uint8_t) VTypes::NaN, true);
        Value_t *cInf = new Value_t(nullptr, (uint8_t) VTypes::INF, true);
        Value_t *cNInf = new Value_t(this, (uint8_t) VTypes::INF, true);

        VMCA(uint8_t *code, size_t cs, Value_t **args, uint8_t argc) {
            SS *mainSS = new DSS();
            Heap *mainHeap = new DHeap();
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

        void *callMain() {
            // TODO:
            return nullptr;
        }

        void *eval(ExecuteContext *c, const uint8_t *b, size_t cs) {
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
#define DMN_KVM_MATH_CASE_ADD(VAL, rX, rY, rZ, TYPE) case VAL: regs->rs[(rZ)] = new TYPE(*(TYPE *) (rX) + *(TYPE *) (rY)); break;
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
                            DMN_KVM_MATH_CASE_ADD(VTypes::INT8, rX, rY, rZ, int8_t)
                            DMN_KVM_MATH_CASE_ADD(VTypes::INT16, rX, rY, rZ, int16_t)
                            DMN_KVM_MATH_CASE_ADD(VTypes::INT32, rX, rY, rZ, int32_t)
                            DMN_KVM_MATH_CASE_ADD(VTypes::INT64, rX, rY, rZ, int64_t)
                            DMN_KVM_MATH_CASE_ADD(VTypes::UINT8, rX, rY, rZ, uint8_t)
                            DMN_KVM_MATH_CASE_ADD(VTypes::UINT16, rX, rY, rZ, uint16_t)
                            DMN_KVM_MATH_CASE_ADD(VTypes::UINT32, rX, rY, rZ, uint32_t)
                            DMN_KVM_MATH_CASE_ADD(VTypes::UINT64, rX, rY, rZ, uint64_t)
                            DMN_KVM_MATH_CASE_ADD(VTypes::FLOAT, rX, rY, rZ, float)
                            DMN_KVM_MATH_CASE_ADD(VTypes::DOUBLE, rX, rY, rZ, double)
                            DMN_KVM_MATH_CASE_ADD(VTypes::CHAR, rX, rY, rZ, char)
                            case VTypes::REFERENCE:
                                regs->rs[rZ] = reinterpret_cast<void *>(reinterpret_cast<intptr_t>(rX) +
                                                                        reinterpret_cast<intptr_t>(rY));
                                break;
                            case VTypes::OBJECT:
                                // TODO:
                                break;
                        }
                    }
#undef DMN_KVM_MATH_CASE_ADD
#define DMN_KVM_MATH_CASE_SUB(VAL, rX, rY, rZ, TYPE) case VAL: regs->rs[(rZ)] = new TYPE(*(TYPE *) (rX) - *(TYPE *) (rY)); break;
                    case C::MTR_SUB: {
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
                            DMN_KVM_MATH_CASE_SUB(VTypes::INT8, rX, rY, rZ, int8_t)
                            DMN_KVM_MATH_CASE_SUB(VTypes::INT16, rX, rY, rZ, int16_t)
                            DMN_KVM_MATH_CASE_SUB(VTypes::INT32, rX, rY, rZ, int32_t)
                            DMN_KVM_MATH_CASE_SUB(VTypes::INT64, rX, rY, rZ, int64_t)
                            DMN_KVM_MATH_CASE_SUB(VTypes::UINT8, rX, rY, rZ, uint8_t)
                            DMN_KVM_MATH_CASE_SUB(VTypes::UINT16, rX, rY, rZ, uint16_t)
                            DMN_KVM_MATH_CASE_SUB(VTypes::UINT32, rX, rY, rZ, uint32_t)
                            DMN_KVM_MATH_CASE_SUB(VTypes::UINT64, rX, rY, rZ, uint64_t)
                            DMN_KVM_MATH_CASE_SUB(VTypes::FLOAT, rX, rY, rZ, float)
                            DMN_KVM_MATH_CASE_SUB(VTypes::DOUBLE, rX, rY, rZ, double)
                            DMN_KVM_MATH_CASE_SUB(VTypes::CHAR, rX, rY, rZ, char)
                            case VTypes::REFERENCE:
                                regs->rs[rZ] = reinterpret_cast<void *>(reinterpret_cast<intptr_t>(rX) -
                                                                        reinterpret_cast<intptr_t>(rY));
                                break;
                            case VTypes::OBJECT:
                                // TODO:
                                break;
                        }
                    }
#undef DMN_KVM_MATH_CASE_SUB
#define DMN_KVM_MATH_CASE_MUL(VAL, rX, rY, rZ, TYPE) case VAL: regs->rs[(rZ)] = new TYPE(*(TYPE *) (rX) * *(TYPE *) (rY)); break;
                    case C::MTR_MUL: {
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
                            DMN_KVM_MATH_CASE_MUL(VTypes::INT8, rX, rY, rZ, int8_t)
                            DMN_KVM_MATH_CASE_MUL(VTypes::INT16, rX, rY, rZ, int16_t)
                            DMN_KVM_MATH_CASE_MUL(VTypes::INT32, rX, rY, rZ, int32_t)
                            DMN_KVM_MATH_CASE_MUL(VTypes::INT64, rX, rY, rZ, int64_t)
                            DMN_KVM_MATH_CASE_MUL(VTypes::UINT8, rX, rY, rZ, uint8_t)
                            DMN_KVM_MATH_CASE_MUL(VTypes::UINT16, rX, rY, rZ, uint16_t)
                            DMN_KVM_MATH_CASE_MUL(VTypes::UINT32, rX, rY, rZ, uint32_t)
                            DMN_KVM_MATH_CASE_MUL(VTypes::UINT64, rX, rY, rZ, uint64_t)
                            DMN_KVM_MATH_CASE_MUL(VTypes::FLOAT, rX, rY, rZ, float)
                            DMN_KVM_MATH_CASE_MUL(VTypes::DOUBLE, rX, rY, rZ, double)
                            DMN_KVM_MATH_CASE_MUL(VTypes::CHAR, rX, rY, rZ, char)
                            case VTypes::REFERENCE:
                                regs->rs[rZ] = reinterpret_cast<void *>(reinterpret_cast<intptr_t>(rX) *
                                                                        reinterpret_cast<intptr_t>(rY));
                                break;
                            case VTypes::OBJECT:
                                // TODO:
                                break;
                        }
                    }
#undef DMN_KVM_MATH_CASE_MUL
#define DMN_KVM_MATH_CASE_DIV(VAL, rX, rY, rZ, TYPE) case VAL: regs->rs[(rZ)] = new TYPE(*(TYPE *) (rX) / *(TYPE *) (rY)); break;
                    case C::MTR_DIV: {
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
                            DMN_KVM_MATH_CASE_DIV(VTypes::INT8, rX, rY, rZ, int8_t)
                            DMN_KVM_MATH_CASE_DIV(VTypes::INT16, rX, rY, rZ, int16_t)
                            DMN_KVM_MATH_CASE_DIV(VTypes::INT32, rX, rY, rZ, int32_t)
                            DMN_KVM_MATH_CASE_DIV(VTypes::INT64, rX, rY, rZ, int64_t)
                            DMN_KVM_MATH_CASE_DIV(VTypes::UINT8, rX, rY, rZ, uint8_t)
                            DMN_KVM_MATH_CASE_DIV(VTypes::UINT16, rX, rY, rZ, uint16_t)
                            DMN_KVM_MATH_CASE_DIV(VTypes::UINT32, rX, rY, rZ, uint32_t)
                            DMN_KVM_MATH_CASE_DIV(VTypes::UINT64, rX, rY, rZ, uint64_t)
                            DMN_KVM_MATH_CASE_DIV(VTypes::FLOAT, rX, rY, rZ, float)
                            DMN_KVM_MATH_CASE_DIV(VTypes::DOUBLE, rX, rY, rZ, double)
                            DMN_KVM_MATH_CASE_DIV(VTypes::CHAR, rX, rY, rZ, char)
                            case VTypes::REFERENCE:
                                regs->rs[rZ] = reinterpret_cast<void *>(reinterpret_cast<intptr_t>(rX) /
                                                                        reinterpret_cast<intptr_t>(rY));
                                break;
                            case VTypes::OBJECT:
                                // TODO:
                                break;
                        }
                    }
#undef DMN_KVM_MATH_CASE_DIV
#define DMN_KVM_MATH_CASE_POW(VAL, rX, rY, rZ, TYPE) case VAL: regs->rs[(rZ)] = new TYPE(*(TYPE *) (rX) ^ *(TYPE *) (rY)); break;
                    case C::MTR_POW: {
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
                            DMN_KVM_MATH_CASE_POW(VTypes::INT8, rX, rY, rZ, int8_t)
                            DMN_KVM_MATH_CASE_POW(VTypes::INT16, rX, rY, rZ, int16_t)
                            DMN_KVM_MATH_CASE_POW(VTypes::INT32, rX, rY, rZ, int32_t)
                            DMN_KVM_MATH_CASE_POW(VTypes::INT64, rX, rY, rZ, int64_t)
                            DMN_KVM_MATH_CASE_POW(VTypes::UINT8, rX, rY, rZ, uint8_t)
                            DMN_KVM_MATH_CASE_POW(VTypes::UINT16, rX, rY, rZ, uint16_t)
                            DMN_KVM_MATH_CASE_POW(VTypes::UINT32, rX, rY, rZ, uint32_t)
                            DMN_KVM_MATH_CASE_POW(VTypes::UINT64, rX, rY, rZ, uint64_t)
                            case VTypes::FLOAT:
                                regs->rs[(rZ)] = new float(std::pow(*(float *) (rX), *(float *) (rY)));
                                break;
                            case VTypes::DOUBLE:
                                regs->rs[(rZ)] = new double(std::pow(*(double *) (rX), *(double *) (rY)));
                                break;
                            DMN_KVM_MATH_CASE_POW(VTypes::CHAR, rX, rY, rZ, char)
                            case VTypes::REFERENCE:
                                regs->rs[rZ] = reinterpret_cast<void *>(reinterpret_cast<intptr_t>(rX) ^
                                                                        reinterpret_cast<intptr_t>(rY));
                                break;
                            case VTypes::OBJECT:
                                // TODO:
                                break;
                        }
                    }
#undef DMN_KVM_MATH_CASE_POW
#define DMN_KVM_MATH_CASE_SQRT(VAL, rX, rY, rZ, TYPE) case VAL: regs->rs[(rZ)] = new TYPE(std::pow(*(TYPE *) (rX), 1 / *(TYPE *) (rY))); break;
                    case C::MTR_SQRT: {
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
                            DMN_KVM_MATH_CASE_SQRT(VTypes::INT8, rX, rY, rZ, int8_t)
                            DMN_KVM_MATH_CASE_SQRT(VTypes::INT16, rX, rY, rZ, int16_t)
                            DMN_KVM_MATH_CASE_SQRT(VTypes::INT32, rX, rY, rZ, int32_t)
                            DMN_KVM_MATH_CASE_SQRT(VTypes::INT64, rX, rY, rZ, int64_t)
                            DMN_KVM_MATH_CASE_SQRT(VTypes::UINT8, rX, rY, rZ, uint8_t)
                            DMN_KVM_MATH_CASE_SQRT(VTypes::UINT16, rX, rY, rZ, uint16_t)
                            DMN_KVM_MATH_CASE_SQRT(VTypes::UINT32, rX, rY, rZ, uint32_t)
                            DMN_KVM_MATH_CASE_SQRT(VTypes::UINT64, rX, rY, rZ, uint64_t)
                            case VTypes::FLOAT:
                                regs->rs[(rZ)] = new float(std::pow(*(float *) (rX), *(float *) (rY)));
                                break;
                            case VTypes::DOUBLE:
                                regs->rs[(rZ)] = new double(std::pow(*(double *) (rX), *(double *) (rY)));
                                break;
                            DMN_KVM_MATH_CASE_SQRT(VTypes::CHAR, rX, rY, rZ, char)
                            case VTypes::REFERENCE:
                                // TODO:
                                break;
                            case VTypes::OBJECT:
                                // TODO:
                                break;
                        }
                    }
#undef DMN_KVM_MATH_CASE_SQRT
                }
            }
            return nullptr;
        }

        static void call(VMCA *vm, ExecuteContext *context) {
            auto method = context->call->method;
            if (typeid(*method) == typeid(BCMethod_t)) {
                Stack<void *> *stack = context->thread->stack;
                stack->push(vm);
                stack->push(context);
                auto m = (BCMethod_t *) method;
                vm->eval(context, m->bc, m->cs);
            } else if (typeid(*method) == typeid(NMethod_t)) {
                ((NMethod_t *) method)->call(new void *[]{vm, context}, 2);
            } else
                ((NRMethod_t *) method)->ref(new void *[]{vm, context}, 2);
        }

        static inline uint8_t RNV(size_t *i, const uint8_t *bytes) {
            return bytes[++(*i)];
        }

        static void createMain(BCMethod_t *ptr, SS *ss, uint8_t *code, size_t cs) {
            new(ptr) BCMethod_t(ss->add("$main()V"), code, cs);
        }
    };
}

#endif /* DMN_KVM_VM_HPP */