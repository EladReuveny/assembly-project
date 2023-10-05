#ifndef  MACHINECODE_H
#define MACHINECODE_H

/**
 * @file machinecode.h
 * @brief Definitions and functions related to machine code generation.
 */

/**
 * @struct CodeWord
 * @brief Structure to represent a single machine code word.
 *
 * This structure holds the binary representation of a machine code word.
 */
typedef struct CodeWord {
    unsigned int binaryCode; /** The binary representation of the machine code word. */
} CodeWord;

/**
 * @brief Array of machine code words.
 *
 * This array holds the generated machine code words during the assembly process.
 * Each element of the array represents a single machine code word with its binary representation.
 */
extern CodeWord codeWordTable[];

/**
 * @brief Generate the binary code for an instruction.
 *
 * This function generates the binary code for an instruction with the specified destination
 * and source operand addressing modes and the opcode.
 *
 * @param destOperandAddressing The destination operand addressing mode (0-7).
 * @param opCode The opcode of the instruction (0-15).
 * @param srcOperandAddressing The source operand addressing mode (0-7).
 * @return The generated 12-bit binary code for the instruction.
 */
unsigned int generateBinaryCode(int destOperandAddressing, int opCode, int srcOperandAddressing);

/**
 * @brief Convert register numbers to a 12-bit binary representation.
 *
 * This function converts two register numbers (destination and source) to a 12-bit binary representation.
 *
 * @param destRegister The number of the destination register (0-7).
 * @param srcRegister The number of the source register (0-7).
 * @return The 12-bit binary representation of the two registers.
 */
unsigned int registersToBinary(int destRegister, int srcRegister);

/**
 * @brief Convert a decimal number to a 12-bit binary representation.
 *
 * This function converts a decimal number to a 12-bit binary representation.
 * If the decimal number cannot be represented using 12 bits, it will be truncated.
 *
 * @param decimal The decimal number to convert.
 * @return The 12-bit binary representation of the decimal number.
 */
unsigned int decimalToBinary12Bit(int decimal);

/**
 * @brief Convert a decimal number to a 10-bit binary representation.
 *
 * This function converts a decimal number to a 10-bit binary representation.
 * If the decimal number cannot be represented using 10 bits, it will be truncated.
 *
 * @param decimal The decimal number to convert.
 * @return The 10-bit binary representation of the decimal number.
 */
unsigned int decimalToBinary10Bit(int decimal);

/**
 * @brief Convert operand and type to a 12-bit binary representation.
 *
 * This function converts an operand value and its type to a 12-bit binary representation.
 *
 * @param operand The operand value to convert.
 * @param type The type of the operand (0-3).
 * @return The 12-bit binary representation of the operand and type.
 */
unsigned int convertTo12BitBinary(int operand, int type);

/**
 * @brief Convert an ASCII character to a 12-bit binary representation.
 *
 * This function converts an ASCII character to its 12-bit binary representation.
 *
 * @param ascii_value The ASCII character to convert.
 * @return The 12-bit binary representation of the ASCII character.
 */
unsigned int asciiToBinary12Bit(char ascii_value);

/**
 * @brief Convert a 12-bit binary number to a base64-encoded string.
 *
 * This function converts a 12-bit binary number to its base64-encoded representation.
 *
 * @param binaryNumber The 12-bit binary number to convert.
 * @return The base64-encoded string representing the binary number.
 */
char* convertToBase64(int binaryNumber);

/**
 * @brief Adds the given binary code to the codeWordTable at the current address.
 *
 * @param fileName The name of the file being processed.
 * @param line The current line being processed.
 * @param binaryCode The binary code to be added to the codeWordTable.
 */
void addToCodeWordTable(const char *fileName, const char *line, unsigned int binaryCode);

#endif
