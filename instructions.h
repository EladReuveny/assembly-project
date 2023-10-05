#ifndef INSTRUCTION_H
#define INSTRUCTION_H

/**
 * @file instructions.h
 * @brief Definitions and functions related to instructions.
 */

/**
 * @struct Instruction
 * @brief Structure to represent an instruction.
 *
 * This structure holds information about an assembly instruction,
 * including its opcode, mnemonic name, and the number of operands it takes.
 */
typedef struct Instruction {
    int code;                /* The opcode of the instruction. */
    char name[4];            /* The name of the instruction. */
    int numOfOperands;       /* The number of operands the instruction takes. */
} Instruction;

/**
 * @brief Array holding the instructions table.
 *
 * This array contains all the instructions supported by the assembler,
 * along with their opcodes, names, and the number of operands they take.
 * It is used to check the existence and obtain information about instructions.
 */
extern Instruction instructionsTable[];

/**
 * @brief Check if an instruction with the given name exists.
 *
 * @param name The name of the instruction to check.
 * @return True if the instruction exists, false otherwise.
 */
int isInstructionExist(const char* name);

/**
 * @brief Get the number of operands for an instruction with the given mnemonic name.
 *
 * This function returns the number of operands an instruction takes based on its mnemonic name.
 *
 * @param name The name of the instruction.
 * @return The number of operands the instruction takes, or -1 if the instruction doesn't exist.
 */
int getInstructionNumOfOperands(const char* name);

/**
 * @brief Get the opcode (code) of an instruction with the given mnemonic name.
 *
 * This function returns the opcode (code) of an instruction based on its mnemonic name.
 *
 * @param name The name of the instruction.
 * @return The opcode of the instruction, or -1 if the instruction doesn't exist.
 */
int getInstructionCode(const char* name);

/**
 * @brief Determines if the addressing methods for the operands are valid for a given instruction.
 *
 * @param opCode The opcode (instruction) for which the addressing methods are being checked.
 * @param addressingMethod1 The addressing method for operand 1.
 * @param addressingMethod2 The addressing method for operand 2.
 * @return True if the addressing methods are valid for the given opcode, false otherwise.
 */
int isValidAddressingMethod(const char* opCode, int addressingMethod1, int addressingMethod2);

#endif
