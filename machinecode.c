#include <malloc.h>
#include "data.h"
#include "machinecode.h"

CodeWord codeWordTable[MAX_CODE_WORD_TABLE_SIZE];

unsigned int generateBinaryCode(int destOperandAddressing, int opCode, int srcOperandAddressing) {
    unsigned int binaryCode = 0;

    /* Set bits 0-1: ARE (Absolute/External/Relocatable) */
    binaryCode |= (0 << 0); /* Bit 0 */
    binaryCode |= (0 << 1); /* Bit 1 */

    /* Set bits 2-4 to the destination operand addressing */
    binaryCode |= (destOperandAddressing << 2); /* Bits 2-4 */

    /* Set bits 5-8 to the opCode */
    binaryCode |= (opCode << 5); /* Bits 5-8 */

    /* Set bits 9-11 to the source operand addressing */
    binaryCode |= (srcOperandAddressing << 9); /* Bits 9-11 */

    return binaryCode;
}

unsigned int registersToBinary(int destRegister, int srcRegister) {
    unsigned int binaryCode = 0;

    /* Set bits 2-6 to the destination operand addressing */
    binaryCode |= (destRegister << 2); /* Bits 2-6 */

    /* Set bits 7-11 to the source operand addressing */
    binaryCode |= (srcRegister << 7); /* Bits 7-11 */

    return decimalToBinary12Bit(binaryCode);
}

/* Function to convert a decimal number to a 10-bit binary number */
unsigned int decimalToBinary10Bit(int decimal) {
    unsigned int binary = 0;
    int bitPosition = 0; /* Starting from the least significant bit (bit 0) */

    while (decimal > 0 && bitPosition < 10) {
        int bit = decimal % 2; /* Get the least significant bit */
        binary |= (bit << bitPosition); /* Set the corresponding bit in the binary number */
        decimal /= 2; /* Right-shift the decimal number */
        bitPosition++; /* Move to the next bit position */
    }

    return binary;
}

/* Function to convert the parameters to a 12-bit binary number */
unsigned int convertTo12BitBinary(int operand, int type) {
    unsigned int binaryOperand = decimalToBinary10Bit(operand);
    unsigned int binaryAddress = type & 0x3; /* Ensure type is within 0-3 range (2 bits) */

    /* Combine the operand and type to form a 12-bit binary number */
    return (binaryOperand << 2) | binaryAddress;
}

unsigned int decimalToBinary12Bit(int decimal) {
    unsigned int binary = 0;
    int bitPosition = 0;
    int isNegative = 0;

    if (decimal < 0) {
        isNegative = 1;
        decimal = -decimal; /* Convert the number to its positive counterpart */
    }

    while (decimal > 0 && bitPosition < 11) {
        /* Get the remainder of the decimal number when divided by 2 */
        int remainder = decimal % 2;
        /* Set the corresponding bit in the binary representation */
        binary |= (remainder << bitPosition);
        /* Divide the decimal number by 2 to get the next bit */
        decimal /= 2;
        /* Move to the next bit position in the binary representation */
        bitPosition++;
    }

    /* Handle the 12th bit (sign bit) in Two's complement notation */
    if (isNegative) {
        binary = ~binary; /* Invert all bits */
        binary &= 0xFFF; /* Ensure only the 12 least significant bits are used */
        binary += 1; /* Add 1 to complete the Two's complement representation */
    }

    return binary;
}

unsigned int asciiToBinary12Bit(char ascii_value) {
    int decimal = (int)ascii_value; /* Convert ASCII value to decimal */
    return decimalToBinary12Bit(decimal);
}

char* convertToBase64(int binaryNumber) {
    /* Base 64 encoding table */
    const char base64Table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    char* base64Number = (char*)malloc(3 * sizeof(char));

    /* Split the 12-bit binary number into two 6-bit segments */
    int segment1 = (binaryNumber >> 6) & 0x3F;
    int segment2 = binaryNumber & 0x3F;

    /* Convert each 6-bit segment into a base 64 character */
    base64Number[0] = base64Table[segment1];
    base64Number[1] = base64Table[segment2];
    base64Number[2] = '\0'; /* Null-terminate the string */

    return base64Number;
}

void addToCodeWordTable(const char *fileName, const char *line, unsigned int binaryCode) {
    if(isValidAddress())
        codeWordTable[address - INITIAL_ADDRESS_VALUE].binaryCode = binaryCode;
    else
        reportError(fileName, 16, line);
}