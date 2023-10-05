#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "data.h"
#include "symbols.h"
#include "utilities.h"
#include "analyze.h"

int isCharacter(char c) {
    /* Check if the character is an uppercase letter (A-Z) or a lowercase letter (a-z) */
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int isLabelDeclaration(const char *fileName, char *line) {
    if(line == NULL)
        return false;

    char copiedLine [MAX_LINE_LENGTH]; /* Create an array to hold the copy of the line */
    strcpy(copiedLine, line); /* Make a copy of the original line */

    char* token = strtok(line, " \t");
    if(strlen(token) > MAX_LABEL_LENGTH)
        reportError(fileName, 9, copiedLine);
    return isCharacter(token[0]) && token[strlen(token) - 1] == ':';
}

int isDirectiveDeclaration(char *directive) {
    return directive[0] == '.';
}

int isNumeric(char* operand) {
    if (operand == NULL) {
        return false; /* Operand is NULL, not a numeric value */
    }

    int i = 0;
    if (operand[0] == '-' || operand[0] == '+') {
        i = 1; /* Skip the sign character */
    }
    for (; operand[i] != '\0'; i++) {
        if (!isdigit(operand[i])) {
            return false; /* Operand is not a numeric value */
        }
    }
    return true; /* Operand is numeric */
}

int getRegister(const char* operand) {
    if (operand == NULL || strlen(operand) < 3)
        return -1;

    if (strncmp(operand, "@r", 2) == 0) {
        operand += 2;

        switch (*operand) {
            case '0':
                return 0;
            case '1':
                return 1;
            case '2':
                return 2;
            case '3':
                return 3;
            case '4':
                return 4;
            case '5':
                return 5;
            case '6':
                return 6;
            case '7':
                return 7;
            default:
                printf("r%c is an invalid register.\n", *operand);
                return -1;
        }
    }
    return -1;
}

int getAddressingMethod(char* operand) {
    if (operand == NULL)
        return -1;

    if (isNumeric(operand))
        return METHOD_IMMEDIATE; /* Immediate addressing - operand is an integer */
    else if (getRegister(operand) != -1)
        return METHOD_DIRECT_REGISTER; /* Direct register addressing - operand is the name of a register */
    return METHOD_DIRECT;
}

void initializeMemory() {
    freeSymbolTable(); /* Free memory allocated for the symbol table */
    freeExternSymbolTable(); /* Free memory allocated for the extern symbol table */

    /* Initialize global variables to their initial value */
    address = 100;
    lineNum = 0;
    directFlag = 0;
    endFirstPassFlag = 0;
    errorFlag = 0;
}

void reportError(const char *fileName, int errorCode, const char *errorMessage) {
    errorFlag = 1;

    /* Skipping second pass errors to avoid duplicate errors. */
    if(endFirstPassFlag)
        return;

    printf("ERROR has been occurred in %s file at line <%d>: %s --->>> ",fileName, lineNum, errorMessage);

    switch (errorCode) {
        case 1:
            printf("*Too Many Operands For Such Instruction*\n");
            break;
        case 2:
            printf("*Missing Operands*\n");
            break;
        case 3:
            printf("*Invalid Operand(s) For Such Instruction*\n");
            break;
        case 4:
            printf("*No Source File Provided*\n");
            break;
        case 5:
            printf("*File Couldn't Be Found/Opened*\n");
            break;
        case 6:
            printf("*No Such Register Exist*\n");
            break;
        case 7:
            printf("*No Such Instruction Exist*\n");
            break;
        case 8:
            printf("*Invalid Directive*\n");
            break;
        case 9:
            printf("*Overflow Label Declaration Exception*\n");
            break;
        case 10:
            printf("*Symbol Is Already Defined As Extern*\n");
            break;
        case 11:
            printf("*Symbol Is Already Defined As Entry*\n");
            break;
        case 12:
            printf("*Memory Allocation Has Been Failed*\n");
            break;
        case 13:
            printf("*Macro Cannot Be Defined As A Reserved KeyWord*\n");
            break;
        case 14:
            printf("*Too Many Operands For Macro Declaration*\n");
            break;
        case 15:
            printf("*Overflow Line Exception*\n");
            break;
        case 16:
            printf("*Memory Access Violation*\n");
            break;
        case 17:
            printf("*Missing Opening Double Quotes*\n");
            break;
        case 18:
            printf("*Missing Closing Double Quotes*\n");
            break;
        case 19:
            printf("*Symbol Is Already Defined*\n");
            break;
        case 20:
            printf("*Invalid Comma At The Beginning Of The Data Directive*\n");
            break;
        case 21:
            printf("*Invalid Comma At The End Of The Data Directive*\n");
            break;
        case 22:
            printf("*Invalid Consecutive Commas At The Data Directive*\n");
            break;
        case 23:
            printf("*Too Many Operands For Ending Macro Declaration*\n");
            break;
        default:
            printf("*Unknown Error*\n");
    }
    printf("\n");
}

int checkNumOfOperands(const char* operand1, const char* operand2, const char* operand3) {
    int cnt = 0;

    if(operand1 != NULL)
        cnt++;
    if(operand2 != NULL)
        cnt++;
    if(operand3 != NULL)
        cnt++;

    return cnt;
}

int isValidAddress() {
    return address < MAX_CODE_WORD_TABLE_SIZE + INITIAL_ADDRESS_VALUE;
}

void tokenizeArguments(char *line, char **directive, char **arguments) {
    if (directFlag == 0) {
        (*directive) = line;
        (*arguments) = strtok(NULL, " ,\t\n");
    } else {
        (*arguments) = strtok(line, " ,\t\n");
        (*directive) = (*arguments);
        (*arguments) = strtok(NULL, " ,\t\n");
    }
}

void checkCommas(const char *fileName, char *line) {
    if(line != NULL) {
        if(!directFlag) {
            char* copyLine = line;
            while (strncmp(copyLine, ".data", 5) != 0)
                copyLine++;
            if(copyLine[6] == ',')
                reportError(fileName, 20, line);
            else if (copyLine[strlen(copyLine) - 1] == ',')
                reportError(fileName, 21, line);
            else if (strstr(copyLine, ",,"))
                reportError(fileName, 22, line);
        } else {
            if (line[10] == ',')
                reportError(fileName, 20, line);
            else if (line[strlen(line) - 1] == ',')
                reportError(fileName, 21, line);
            else if (strstr(line, ",,"))
                reportError(fileName, 22, line);
        }
    }
}

void processDataDirective(const char *fileName, const char *copiedLine, char *arguments) {
    while (arguments != NULL && isNumeric(arguments)) {
        unsigned int binaryCode = decimalToBinary12Bit(strtol(arguments,
                                                              NULL, 10));
        addToCodeWordTable(fileName, copiedLine, binaryCode);
        address++;
        arguments = strtok(NULL, " ,\t");
    }
}

void processStringDirective(const char *fileName, const char *copiedLine, char *arguments) {
    /* Check for valid string enclosed with double quotes */
    /* Missing opening double quotes */
    if (*arguments != '\"') {
        reportError(fileName, 17, copiedLine);
        return;
    }
    /* Missing closing double quotes */
    if (arguments[strlen(arguments) - 1] != '\"') {
        reportError(fileName, 18, copiedLine);
        return;
    }

    arguments++; /* Skip first " quotation occurrence */
    unsigned int binaryCode;
    while (arguments != NULL && *arguments != '\0' && *arguments != '\"') {
        /* Skipping non alphabetic characters */
        if (!isCharacter(*arguments)) {
            arguments++;
            continue;
        }

        /* Current character is alphabetic */
        binaryCode = asciiToBinary12Bit(*arguments);
        addToCodeWordTable(fileName, copiedLine, binaryCode);
        address++;
        arguments++;
    }

    /* Including the '\0' of the string */
    binaryCode = asciiToBinary12Bit('\0');
    addToCodeWordTable(fileName, copiedLine, binaryCode);
    address++;
}

void processEntryDirective(const char *fileName, const char *copiedLine, char *arguments) {
    /* Setting entry symbol into the symbol table */
    do {
        /* Remove carriage return character from the symbol name */
        arguments[strcspn(arguments, "\r\n")] = '\0';

        /* Process entry directive according to it's existence in the symbol table */
        char *symbolName = arguments;
        if (!isSymbolExist(symbolName)) /* Symbol isn't exist yet in the symbol table */
            addToSymbolTable(fileName, symbolName, 0, 1, 0);
        else {
            /* Mark the symbol as an entry point in the symbol table if not marked as extern yet*/
            if (!isExtern(symbolName))
                setEntrySymbol(symbolName);
            else /* Report error for attempting to mark a symbol both as an entry point and as an extern point */
                reportError(fileName, 10, copiedLine);
        }
        /* Tokenizing the rest of the symbols if there are any left */
        arguments = strtok(NULL, " ,\t");
    } while (arguments != NULL);
}

void processExternDirective(const char *fileName, const char *copiedLine, char *arguments) {
    do {
        /* Process external directive */
        char *symbolName = arguments;

        /* Add the symbol to the symbol table with a temporary value if symbol isn't exist yet */
        if (!isSymbolExist(symbolName))
            addToSymbolTable(fileName, symbolName, 0, 0, 1);
        else {
            /* Mark the symbol as an extern point in the symbol table  if not marked at entry point */
            if (!isEntry(symbolName))
                setExternSymbol(symbolName);
            else /* Report error for attempting to mark a symbol both as an entry point and as an extern point */
                reportError(fileName, 11, copiedLine);
        }
        arguments = strtok(NULL, " ,\t"); /* Tokenizing the rest of the symbols if there are any left */
    } while (arguments != NULL);
}

void processInstructionWith0Operands(const char *fileName, const char *copiedLine, const char *opCode) {
    unsigned int binaryCode = generateBinaryCode(0, getInstructionCode(opCode), 0);
    addToCodeWordTable(fileName, copiedLine, binaryCode);
    address++;
}

void processInstructionWith1Operands(const char *fileName, const char *copiedLine, const char *opCode, const char *operand1, int addressingMethod1) {
    unsigned int binaryCode;
    if (addressingMethod1 == METHOD_IMMEDIATE) {
        binaryCode = generateBinaryCode(addressingMethod1, getInstructionCode(opCode), 0);
        addToCodeWordTable(fileName, copiedLine, binaryCode);
        address++;
        binaryCode = decimalToBinary12Bit(strtol(operand1, NULL, 10));
        addToCodeWordTable(fileName, copiedLine, binaryCode);
    } else if (addressingMethod1 == METHOD_DIRECT) {
        binaryCode = generateBinaryCode(addressingMethod1, getInstructionCode(opCode), 0);
        addToCodeWordTable(fileName, copiedLine, binaryCode);
        address++;
        binaryCode = convertTo12BitBinary(getSymbolValue(operand1), getSymbolType(operand1));
        addToCodeWordTable(fileName, copiedLine, binaryCode);
        /* Add operand to extern symbol table while the second pass is being processed */
        if (isExtern(operand1) && endFirstPassFlag == 1)
            addToExternSymbolTable(fileName, operand1, address);
    } else if (addressingMethod1 == METHOD_DIRECT_REGISTER) {
        binaryCode = registersToBinary(0, getRegister(operand1));
        addToCodeWordTable(fileName, copiedLine, binaryCode);
    }
    address++;
}

void processInstructionWith2Operands(const char *fileName, const char *copiedLine, const char *opCode, const char *operand1, int addressingMethod1, int addressingMethod2, const char *operand2) {
    unsigned int binaryCode;

    binaryCode = generateBinaryCode(addressingMethod2, getInstructionCode(opCode), addressingMethod1);
    addToCodeWordTable(fileName, copiedLine, binaryCode);
    address++;

    if (addressingMethod1 == METHOD_DIRECT_REGISTER && addressingMethod2 == METHOD_DIRECT_REGISTER) {
        if (getRegister(operand1) != -1 && getRegister(operand2) != -1) {
            binaryCode = registersToBinary(getRegister(operand2), getRegister(operand1));
            addToCodeWordTable(fileName, copiedLine, binaryCode);
            address++;
        } else if (getRegister(operand1) == -1)
            reportError(fileName, 6, copiedLine);
        else
            reportError(fileName, 6, copiedLine);
    } else if (addressingMethod1 == METHOD_DIRECT_REGISTER && addressingMethod2 == METHOD_DIRECT) {
        binaryCode = registersToBinary(0, getRegister(operand1));
        addToCodeWordTable(fileName, copiedLine, binaryCode);
        address++;
        binaryCode = convertTo12BitBinary(getSymbolValue(operand2), getSymbolType(operand2));
        addToCodeWordTable(fileName, copiedLine, binaryCode);
        /* Add operand to extern symbol table while the second pass is being processed */
        if (isExtern(operand2) && endFirstPassFlag == 1)
            addToExternSymbolTable(fileName, operand2, address);
        address++;
    } else if (addressingMethod1 == METHOD_DIRECT && addressingMethod2 == METHOD_IMMEDIATE) {
        binaryCode = generateBinaryCode(addressingMethod2, getInstructionCode(opCode), addressingMethod1);
        addToCodeWordTable(fileName, copiedLine, binaryCode);
        /* Add operand to extern symbol table while the second pass is being processed */
        if (isExtern(operand1) && endFirstPassFlag == 1)
            addToExternSymbolTable(fileName, operand1, address);
        address++;
        binaryCode = convertTo12BitBinary(getSymbolValue(operand2), getSymbolType(operand2));
        addToCodeWordTable(fileName, copiedLine, binaryCode);
        address++;
    }
}
