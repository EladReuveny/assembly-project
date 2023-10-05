#include <string.h>
#include "data.h"
#include "instructions.h"

Instruction instructionsTable[] = {
        {0,  "mov", 2},
        {1,  "cmp", 2},
        {2,  "add", 2},
        {3,  "sub", 2},
        {4,  "not", 1},
        {5,  "clr", 1},
        {6,  "lea", 2},
        {7,  "inc", 1},
        {8,  "dec", 1},
        {9,  "jmp", 1},
        {10, "bne", 1},
        {11, "red", 1},
        {12, "prn", 1},
        {13, "jsr", 1},
        {14, "rts", 0},
        {15, "stop", 0}
};

int isInstructionExist(const char *name) {
    int i = 0;
    for (; i < INSTRUCTIONS_LENGTH; ++i) {
        /* Instruction's name has been found */
        if(strcmp(instructionsTable[i].name, name) == 0)
            return true;
    }
    return false;
}

int getInstructionNumOfOperands(const char* name) {
    int i = 0;
    for (; i < INSTRUCTIONS_LENGTH; ++i) {
        /* Instruction's name has been found */
        if(strcmp(instructionsTable[i].name, name) == 0)
            return instructionsTable[i].numOfOperands;
    }
    return -1;
}

int getInstructionCode(const char* name) {
    int i = 0;
    for (; i < INSTRUCTIONS_LENGTH; ++i) {
        /* Instruction's name has been found */
        if(strcmp(instructionsTable[i].name, name) == 0)
            return instructionsTable[i].code;
    }
    return -1;
}

int isValidAddressingMethod(const char* opCode, int addressingMethod1, int addressingMethod2) {
    /* Check if the opcode is a three-operand instruction (e.g., mov, add, sub) */
    if (strcmp(opCode, "mov") == 0 || strcmp(opCode, "add") == 0 || strcmp(opCode, "sub") == 0) {
        /* Valid addressing methods for three-operand instructions are:
           (source: immediate, direct, direct register) and (destination: direct, direct register) */
        if ((addressingMethod1 == METHOD_IMMEDIATE || addressingMethod1 == METHOD_DIRECT || addressingMethod1 == METHOD_DIRECT_REGISTER) &&
            (addressingMethod2 == METHOD_DIRECT || addressingMethod2 == METHOD_DIRECT_REGISTER))
            return true;
        return false;
    }
        /* Check if the opcode is a two-operand instruction (e.g., cmp) */
    else if (strcmp(opCode, "cmp") == 0) {
        /* Valid addressing methods for two-operand instructions are:
           (operand1: immediate, direct, direct register) and (operand2: immediate, direct, direct register) */
        if ((addressingMethod1 == METHOD_IMMEDIATE || addressingMethod1 == METHOD_DIRECT || addressingMethod1 == METHOD_DIRECT_REGISTER) &&
            (addressingMethod2 == METHOD_IMMEDIATE || addressingMethod2 == METHOD_DIRECT || addressingMethod2 == METHOD_DIRECT_REGISTER))
            return true;
        return false;
    }
        /* Check if the opcode is a one-operand instruction (e.g., not, clr, inc, dec, jmp, bne, red, jsr) */
    else if (strcmp(opCode, "not") == 0 || strcmp(opCode, "clr") == 0 || strcmp(opCode, "inc") == 0 ||
             strcmp(opCode, "dec") == 0 || strcmp(opCode, "jmp") == 0 || strcmp(opCode, "bne") == 0 ||
             strcmp(opCode, "red") == 0 || strcmp(opCode, "jsr") == 0) {
        /* Valid addressing methods for one-operand instructions are:
           operand1: no addressing method, operand2: direct, direct register */
        if (addressingMethod1 == -1 && (addressingMethod2 == METHOD_DIRECT || addressingMethod2 == METHOD_DIRECT_REGISTER))
            return true;
        return false;
    }
        /* Check if the opcode is the "prn" instruction */
    else if (strcmp(opCode, "prn") == 0) {
        /* Valid addressing methods for the "prn" instruction are:
           operand1: no addressing method, operand2: immediate, direct, direct register */
        if (addressingMethod1 == -1 &&
            (addressingMethod2 == METHOD_IMMEDIATE || addressingMethod2 == METHOD_DIRECT || addressingMethod2 == METHOD_DIRECT_REGISTER))
            return true;
        return false;
    }
        /* Check if the opcode is the "rts" or "stop" instruction */
    else if (strcmp(opCode, "rts") == 0 || strcmp(opCode, "stop") == 0 ) {
        /* Valid addressing methods for the "rts" and "stop" instructions are:
           operand1 and operand2: no addressing method */
        if (addressingMethod1 == -1 && addressingMethod2 == -1)
            return true;
        return false;
    }
        /* Check if the opcode is the "rts" instruction (duplicate entry, assuming it was meant for another opcode) */
    else if (strcmp(opCode, "rts") == 0) {
        /* Valid addressing method for the "rts" instruction is:
           operand1: direct, operand2: direct, direct register */
        if (addressingMethod1 == METHOD_DIRECT && (addressingMethod2 == METHOD_DIRECT || addressingMethod2 == METHOD_DIRECT_REGISTER))
            return true;
        return false;
    }

    /* Return false for any other opcode (invalid opcode) */
    return false;
}