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
        BCMethod_t *main = (BCMethod_t *) malloc(sizeof(BCMethod_t));
        //
        Value_t *cUndefined = new Value_t(nullptr, (uint8_t) VTypes::UNDEFINED, true);
        Value_t *cNaN = new Value_t(nullptr, (uint8_t) VTypes::NaN, true);
        Value_t *cInf = new Value_t(nullptr, (uint8_t) VTypes::INF, true);
        Value_t *cNInf = new Value_t(this, (uint8_t) VTypes::INF, true);

        VMCA(uint8_t *code, size_t cs, Value_t **args, uint8_t argc) {
            auto *mainSS = new DSS();
            auto *mainHeap = new DHeap();
            auto mainCall = new Call{
                    .obj_caller = nullptr,
                    .method_caller = nullptr,
                    .obj = nullptr,
                    .method = main,
                    .args = args,
                    .argc = argc
            };
            auto mainThread = new Thread{
                    .cs = new Stack<Call *>(new SDL::Node(mainCall)),
                    .stack = new Stack<void *>(nullptr),
                    .regs = new Resisters(code[0]),
            };
            mainContext = new ExecuteContext{
                    .call = mainCall,
                    .thread = mainThread,
                    .process = new Process{
                            .threads = new Thread *[]{mainThread},
                            .tc = 1,
                            .heap = mainHeap,
                            .strings = mainSS
                    },
                    .bcPtr = 1
            };
            createMain(main, mainSS, code, cs);
        }

        void *callMain() {
            return eval(mainContext, main->bc, main->cs);
        }

        void *eval(ExecuteContext *c, const uint8_t *b, size_t cs) {
            auto process = c->process;
            auto thread = c->thread;
            auto regs = thread->regs;
            auto stack = thread->stack;
            auto call = c->call;

            for (size_t *i = &c->bcPtr; *i < cs; (*i)++) {
                using C = DmN::KVM::KBC::BC;
                using Primitive = DmN::KVM::KBC::Primitive;
                switch (b[*i]) {// TODO:
                    case C::NOP:
                        break;
                    case C::MR:
                        regs->rs[RNV(i, b)] = GR<void>(regs, i, b);
                        break;
                    case C::MRT:
                        memcpy(GR<uint64_t>(regs, i, b) + RNV(i, b), GR<uint64_t>(regs, i, b) + RNV(i, b), RNV(i, b));
                        break;
                    case C::SR: {
                        auto regAI = RNV(i, b);
                        auto regBI = RNV(i, b);
                        auto regA = GR<void>(regs, regAI);
                        auto regB = GR<void>(regs, regBI);
                        regs->rs[regAI] = regB;
                        regs->rs[regBI] = regA;
                        break;
                    }
                    case C::LCV:
                        switch (RNV(i, b)) {
                            case Primitive::INT8:
                            case Primitive::UINT8:
                                regs->rs[RNV(i, b)] = new uint8_t(RNV(i, b));
                                break;
                            case Primitive::INT16:
                            case Primitive::UINT16:
                                regs->rs[RNV(i, b)] = new uint16_t((RNV(i, b) << 8) | RNV(i, b));
                                break;
                            case Primitive::INT32:
                            case Primitive::UINT32:
                                regs->rs[RNV(i, b)] = new uint32_t(
                                        (RNV(i, b) << 24) | (RNV(i, b) << 16) | (RNV(i, b) << 8) | RNV(i, b));
                                break;
                            case Primitive::INT64:
                            case Primitive::UINT64:
                                regs->rs[RNV(i, b)] = new uint64_t(
                                        (((uint64_t) RNV(i, b) << 0) + ((uint64_t) RNV(i, b) << 8) +
                                         ((uint64_t) RNV(i, b) << 16) + ((uint64_t) RNV(i, b) << 24) +
                                         ((uint64_t) RNV(i, b) << 32) + ((uint64_t) RNV(i, b) << 40) +
                                         ((uint64_t) RNV(i, b) << 48) +
                                         ((uint64_t) RNV(i, b) << 56)));
                                break;
                        }
                        break;
                    case C::LPV:
                        regs->rs[RNV(i, b)] = parseValue(i, b, false);
                        break;
                    case C::LUPV:
                        regs->rs[RNV(i, b)] = GR<Value_t>(regs, i, b)->value;
                        break;
                    case C::PCV:
                        switch (RNV(i, b)) {
                            case Primitive::INT8:
                            case Primitive::UINT8:
                                stack->push(new uint8_t(RNV(i, b)));
                                break;
                            case Primitive::INT16:
                            case Primitive::UINT16:
                                stack->push(new uint16_t((RNV(i, b) << 8) | RNV(i, b)));
                                break;
                            case Primitive::INT32:
                            case Primitive::UINT32:
                                stack->push(new uint32_t(
                                        (RNV(i, b) << 24) | (RNV(i, b) << 16) | (RNV(i, b) << 8) | RNV(i, b)));
                                break;
                            case Primitive::INT64:
                            case Primitive::UINT64:
                                stack->push(new uint64_t(((uint64_t) RNV(i, b) + ((uint64_t) RNV(i, b) << 8) +
                                                          ((uint64_t) RNV(i, b) << 16) + ((uint64_t) RNV(i, b) << 24) +
                                                          ((uint64_t) RNV(i, b) << 32) + ((uint64_t) RNV(i, b) << 40) +
                                                          ((uint64_t) RNV(i, b) << 48) +
                                                          ((uint64_t) RNV(i, b) << 56))));
                                break;
                        }
                        break;
                    case C::PPV:
                        stack->push(parseValue(i, b, false));
                        break;
                    case C::CR:
                        regs->rs[RNV(i, b)] = nullptr;
                        break;
                    case C::CSV:
                        stack->push(stack->peek());
                        break;
                    case C::SS: {
                        auto x = stack->peekPop();
                        auto y = stack->peekPop();
                        stack->push(x);
                        stack->push(y);
                        break;
                    }
                    case C::PV:
                        stack->pop();
                        break;
                    case C::CS:
                        stack->clear();
                        break;
                    case C::LTS:
                        stack->push(GR<void>(regs, i, b));
                        break;
                    case C::LFS:
                        regs->rs[RNV(i, b)] = stack->peekPop();
                        break;
                    case C::ADD: { // TODO: TEST
                        auto reg0 = GR<Value_t>(regs, i, b);
                        auto reg1 = GR<Value_t>(regs, i, b);
                        //
                        auto reg2 = checkAdd(reg0, reg1, cInf, cNInf);
                        if (reg2 == nullptr)
                            reg2 = checkAdd(reg0, reg1, cNInf, cInf);
                        if (reg2 == nullptr)
                            reg2 = checkNanAdd(reg0, reg1, cNaN);
                        if (reg2 == nullptr) {
                            int32_t *x0 = nullptr;
                            int64_t *x1 = nullptr;
                            double *x2 = nullptr;
                            int32_t *y0 = nullptr;
                            int64_t *y1 = nullptr;
                            double *y2 = nullptr;

                            parseValue(reg0, x0, x1, x2);
                            parseValue(reg1, y0, y1, y2);

                            if (x0 == nullptr) {
                                if (x1 == nullptr) {
                                    if (y0 == nullptr) {
                                        if (y1 == nullptr)
                                            regs->rs[RNV(i, b)] = new Value_t(new double(*x2 + *y2),
                                                                              (uint8_t) VTypes::DOUBLE, true);
                                        else
                                            regs->rs[RNV(i, b)] = new Value_t(new double(*x2 + *y1),
                                                                              (uint8_t) VTypes::DOUBLE, true);
                                    } else
                                        regs->rs[RNV(i, b)] = new Value_t(new double(*x2 + *y0),
                                                                          (uint8_t) VTypes::DOUBLE, true);
                                } else {
                                    if (y0 == nullptr) {
                                        if (y1 == nullptr)
                                            regs->rs[RNV(i, b)] = new Value_t(new double(*x1 + *y2),
                                                                              (uint8_t) VTypes::DOUBLE, true);
                                        else
                                            regs->rs[RNV(i, b)] = new Value_t(new int64_t(*x1 + *y1),
                                                                              (uint8_t) VTypes::INT64, true);
                                    } else
                                        regs->rs[RNV(i, b)] = new Value_t(new int64_t(*x1 + *y0),
                                                                          (uint8_t) VTypes::INT64, true);
                                }
                            } else {
                                if (y0 == nullptr) {
                                    if (y1 == nullptr)
                                        regs->rs[RNV(i, b)] = new Value_t(new double(*x0 + *y0),
                                                                          (uint8_t) VTypes::DOUBLE, true);
                                    else {
                                        int64_t res = *x0 + *y1;
                                        if (res > INT32_MAX)
                                            regs->rs[RNV(i, b)] = new Value_t(new int64_t(res), (uint8_t) VTypes::INT64,
                                                                              true);
                                        else
                                            regs->rs[RNV(i, b)] = new Value_t(new int32_t(res), (uint8_t) VTypes::INT32,
                                                                              true);
                                    }
                                } else {
                                    int64_t res = *x0 + *y0;
                                    if (res > INT32_MAX)
                                        regs->rs[RNV(i, b)] = new Value_t(new int64_t(res), (uint8_t) VTypes::INT64,
                                                                          true);
                                    else
                                        regs->rs[RNV(i, b)] = new Value_t(new int32_t(res), (uint8_t) VTypes::INT32,
                                                                          true);
                                }
                            }
                        }
                        break;
                    }
                    case C::CGH: {
                        auto method = (Method_t *) process->heap->getWN(*GR<SI_t>(regs, i, b));
                        auto context = new ExecuteContext{
                                .call = new Call{
                                        .obj_caller = call->obj,
                                        .method_caller = call->method,
                                        .obj = nullptr,
                                        .method = method,
                                        .args = nullptr,
                                        .argc = 0
                                },
                                .thread = thread,
                                .process = process,
                                .bcPtr = 0,
                                .prevContext = c
                        };

                        if (method->isNative)
                            ((NMethod_t *) method)->call(new void *[]{this, context}, 2);
                        else
                            eval(context, ((BCMethod_t *) method)->bc, ((BCMethod_t *) method)->cs);
                        break;
                    }
                    case C::CNS: {
                        auto bytes = new List<char>();
                        auto byte = RNV(i, b);
                        while (byte != '\0') {
                            bytes->add(byte);
                            byte = RNV(i, b);
                        }
                        bytes->add('\0');
                        char *str = new char[bytes->size()];
                        for (size_t j = 0; j < bytes->size(); j++)
                            str[j] = bytes->get(j);
                        stack->push(new SI_t(process->strings->add(str)));
                        break;
                    }
                    case C::AR:
                        regs->rs[RNV(i, b)] = malloc(*GR<uint16_t>(regs, i, b));
                        break;
                    case C::ACR:
                        regs->rs[RNV(i, b)] = malloc((RNV(i, b) << 8) | RNV(i, b));
                        break;
                    case C::FR: {
                        auto r = RNV(i, b);
                        free(regs->rs[r]);
                        regs->rs[r] = nullptr;
                        break;
                    }
                    case C::ASR:
                        regs->rs[RNV(i, b)] = alloca(*GR<uint16_t>(regs, i, b));
                        break;
                    case C::ASCR:
                        regs->rs[RNV(i, b)] = alloca((RNV(i, b) << 8) | RNV(i, b));
                        break;
                    case C::BR:
                        regs->rs[RNV(i, b)] = new void **(GR<void *>(regs, i, b));
                        break;
                    case C::UBR:
                        void **reg = GR<void *>(regs, i, b);
                        regs->rs[RNV(i, b)] = *reg;
                        delete reg;
                }
            }

            return stack->getLastNode() == nullptr ? nullptr : stack->getLast();
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

        template<typename T>
        static inline T *&GR(Resisters *regs, uint8_t i) {
            return (T *&) regs->rs[i];
        }

        template<typename T>
        static inline T *&GR(Resisters *regs, size_t *i, const uint8_t *bytes) {
            return GR<T>(regs, RNV(i, bytes));
        }

        static void createMain(BCMethod_t *ptr, SS *ss, uint8_t *code, size_t cs) {
            new(ptr) BCMethod_t(ss->add("$main()V"), code, cs);
        }

        static inline Value_t *parseValue(size_t *i, const uint8_t *b, bool isCollectable) {
            int8_t type = -1;
            void *value;
            //
            switch (RNV(i, b)) {
                case KBC::Primitive::INT8:
                    type = (uint8_t) VTypes::INT8;
                    value = new uint8_t(RNV(i, b));
                    break;
                case KBC::Primitive::UINT8:
                    type = (uint8_t) VTypes::UINT8;
                    value = new uint8_t(RNV(i, b));
                    break;
                case KBC::Primitive::INT16:
                    type = (uint8_t) VTypes::INT16;
                    value = new uint16_t((RNV(i, b) << 8) | RNV(i, b));
                    break;
                case KBC::Primitive::UINT16:
                    type = (uint8_t) VTypes::UINT16;
                    value = new uint16_t((RNV(i, b) << 8) | RNV(i, b));
                    break;
                case KBC::Primitive::INT32:
                    type = (uint8_t) VTypes::INT32;
                    value = new uint32_t(
                            (RNV(i, b) << 24) | (RNV(i, b) << 16) | (RNV(i, b) << 8) | RNV(i, b));
                    break;
                case KBC::Primitive::UINT32:
                    type = (uint8_t) VTypes::UINT32;
                    value = new uint32_t(
                            (RNV(i, b) << 24) | (RNV(i, b) << 16) | (RNV(i, b) << 8) | RNV(i, b));
                    break;
                case KBC::Primitive::INT64:
                    type = (uint8_t) VTypes::INT64;
                    value = new int64_t(
                            ((int64_t) RNV(i, b) << 56) | ((int64_t) RNV(i, b) << 48) | ((int64_t) RNV(i, b) << 40) |
                            ((int64_t) RNV(i, b) << 32) | (RNV(i, b) << 24) | (RNV(i, b) << 16) | (RNV(i, b) << 8) |
                            RNV(i, b));
                    break;
                case KBC::Primitive::UINT64:
                    type = (uint8_t) VTypes::UINT64;
                    value = new uint64_t(
                            ((uint64_t) RNV(i, b) << 56) | ((uint64_t) RNV(i, b) << 48) | ((uint64_t) RNV(i, b) << 40) |
                            ((uint64_t) RNV(i, b) << 32) | (RNV(i, b) << 24) | (RNV(i, b) << 16) | (RNV(i, b) << 8) |
                            RNV(i, b));
                    break;
                case KBC::Primitive::FLOAT: {
                    // TODO:
                    break;
                }
                case KBC::Primitive::DOUBLE: {// TODO:
                    type = (uint8_t) VTypes::DOUBLE;
                    value = new double;
                    uint8_t bytes[8] = {RNV(i, b), RNV(i, b), RNV(i, b), RNV(i, b), RNV(i, b), RNV(i, b), RNV(i, b),
                                        RNV(i, b)};
                    memcpy(value, bytes, 8);
                    break;
                }
            }
            //
            return new Value_t(value, type, isCollectable);
        }

        static Value_t *checkAdd(Value_t *v0, Value_t *v1, Value_t *value0, Value_t *value1) {
            if (value0 == v0) {
                if (value1 == v1)
                    return new Value_t(new uint32_t(0), 5, true);
                else return value0;
            }
            return nullptr;
        }

        static Value_t *checkNanAdd(Value_t *v0, Value_t *v1, Value_t *nan) {
            if (v0 == nan || v1 == nan)
                return nan;
            return nullptr;
        }

        static void parseValue(Value_t *reg, int32_t *&x, int64_t *&y, double *&z) {
            if (reg->type == (uint8_t) VTypes::INT8 || reg->type == (uint8_t) VTypes::UINT8) {
                x = new int32_t;
                memcpy(x, reg->value, 8);
            } else if (reg->type == (uint8_t) VTypes::INT16 || reg->type == (uint8_t) VTypes::UINT16) {
                x = new int32_t;
                memcpy(x, reg->value, 16);
            } else if (reg->type == (uint8_t) VTypes::INT32 || reg->type == (uint8_t) VTypes::UINT32)
                x = (int32_t *) reg->value;
            else if (reg->type == (uint8_t) VTypes::INT64 || reg->type == (uint8_t) VTypes::UINT64)
                y = (int64_t *) reg->value;
            else if (reg->type == (uint8_t) VTypes::FLOAT) {
                z = new double;
                memcpy(z, reg->value, sizeof(float));
            } else if (reg->type == (uint8_t) VTypes::DOUBLE)
                z = (double *) reg->value;
            else throw "!Add Opcode : Unknown Type!";
        }
    };
}

#endif /* DMN_KVM_VM_HPP */