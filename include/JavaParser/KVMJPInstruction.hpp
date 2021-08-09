#ifndef DMN_KVM_NO_PRAGMA
#pragma once
#endif /* DMN_KVM_NO_USE_PRAGMA */
#ifndef DMNKVM_KVMJPINSTRUCTION_HPP
#define DMNKVM_KVMJPINSTRUCTION_HPP

#include <KVMJPComm.hpp>

namespace DmN::KVM::JP {
    typedef struct MethodEntry MethodEntry;

    typedef bool (*HandlerFunc)(void *);

    typedef struct CasePair {
        int value;
        U4  position;
    } CasePair;

    typedef struct TableSwitch {
        int caseMin;
        int caseMax;
        U4 defaultPos;
        U4 pairCnt;
        CasePair *pairs;
    } TableSwitch;

    typedef struct LookupSwitch {
        U4 defaultPos;
        U4 pairCnt;
        CasePair *pairs;
    } LookupSwitch;

    typedef struct {
        U1 opcode;		      // opcode
        char *name;		      // name of opcode
        union {
            U1 u1;
            U2 u2;
            U4 u4;
            U8 u8;
            TableSwitch  tblSw;
            LookupSwitch lkpSw;
        } operand;		      // operand
        U1 tag;			      // indicate the valid operand

        /*
           It usually equals tag + 1,
           However, tblSw & lkpSw are variable length instructions
           */
        U2 length;            // the length of the instruction
        HandlerFunc handler;  // handler of opcode
        U1 reserve;           // reserve field for reuse tag
    } Instruction;

    typedef struct ExecEnv ExecEnv;
    /**
     * Instruction execute environment
     */
    typedef struct InstExecEnv {
        Instruction *inst;
        MethodEntry *method;
        int method_pos;
        ExecEnv *env;
    } InstExecEnv;

    /**
     * Validate whether the opcode is valid
     * return:
     *		TURE  valid
     *		FALSE invalid
     */
    bool validate_opcode(int opcode);

    /**
     * Retrieve the opcode's name
     * Return:
     *		opcode's name if valid
     *		"Invalid opcode" if invalid
     * Notice:
     do not free me
     */
    const char* stropcode(int opcode);

    /**
     * Get a instruction in the buffer
     * Param:
    buff:		the byte code stream
    codelen:	code's length
     * Return:
     A pointer of the instruction if valid opcode
     NULL if invalid opcode
     * Notice:
     do not free me
     */
    const Instruction* getCachedInstruction(U1 *code, int codelen, int offset);

    /**
     * Log the instruction info
     */
    void logInstruction(const Instruction *inst);

    /**
     * Get the opcode of the specified instruction
     */
    U1 getInstOpcode(const Instruction *inst);
}

#endif /* DMNKVM_KVMJPINSTRUCTION_HPP */
