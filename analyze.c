#include <stdio.h>
#include <string.h>
#include "data.h"
#include "symbols.h"
#include "machinecode.h"
#include "utilities.h"
#include "analyze.h"
#include "instructions.h"

int address = INITIAL_ADDRESS_VALUE;
int lineNum = 0;
int directFlag = 0;
int endFirstPassFlag = 0;
int errorFlag = 0;

void processLabelDeclaration(const char *fileName, char *line) {
    char copiedLine[MAX_LINE_LENGTH]; /* Create an array to hold the copy of the line */
    strcpy(copiedLine, line); /* Make a copy of the original line */
    char *token = strtok(line, " \t\n");

    /* Add the label to the symbol table with the current address */
    char *label = token;
    label[strlen(label) - 1] = '\0'; /* Remove the ':' character from the label */

    /* Add symbol to the symbol table if not exist yet, otherwise update it's address */
    if (!isSymbolExist(label) && !endFirstPassFlag)
        addToSymbolTable(fileName, label, address, 0, 0);
    else {
        /* Update the symbol's value if it's value is casual, a value that is 0 */
        if(getSymbolValue(label) == 0)
            updateSymbolTable(label, address);
        else        /* The symbol is already exist and it's value isn't casual, meaning it's value unequal to 0 */
            if(!endFirstPassFlag) {     /* Skip second pass, meaning still processing first pass */
                reportError(fileName, 19, copiedLine);   /* Report an error for a duplicated symbol */
                return;
            }
    }

    token = strtok(NULL, " \t\n"); /* Move to the next part of the line */

    /* Check for directive/instruction */
    if (token != NULL) {
        if (strcmp(token, ".data") == 0 || strcmp(token, ".string") == 0 ||
            strcmp(token, ".entry") == 0 || strcmp(token, ".extern") == 0)
            processDirective(fileName, token, copiedLine);
        else
            processInstruction(fileName, token, copiedLine);
    } else /* Missing Operands - No operands have been found */
        reportError(fileName, 2, copiedLine);
}

void processInstruction(const char *fileName, char *line, const char *orgLine) {
    char *token;
    char *opCode;
    char copiedLine [MAX_LINE_LENGTH]; /* Create an array to hold the copy of the line */
    strcpy(copiedLine, line); /* Make a copy of the line */

    /* Tokenizing according to the last source whom has been tokenized */
    tokenizeArguments(line, &opCode, &token);

    /* Remove new line/carriage return character from the instruction name */
    opCode[strcspn(opCode, "\r\n")] = '\0';

    /* Check existence of opCode in the instruction table */
    if (isInstructionExist(opCode)) {
        /* Tokenize the line to extract the opCode and operands */
        char *operand1;
        char *operand2;
        char *operand3;
        int addressingMethod1, addressingMethod2;
        int expectedOperands = getInstructionNumOfOperands(opCode);
        operand1 = token;
        token = strtok(NULL, " ,\t\n");
        operand2 = token;

        /* Getting addressing method for each operand */
        addressingMethod1 = getAddressingMethod(operand1);
        addressingMethod2 = getAddressingMethod(operand2);
        token = strtok(NULL, " ,\t\n");
        operand3 = token;

        /* Report error if addressing method isn't valid*/
        if (!isValidAddressingMethod(opCode, addressingMethod2, addressingMethod1)) {
            reportError(fileName, 3, orgLine);
            return;
        }

        /* Report error if num of operands of instruction is larger/lower than expected operands of current instruction */
        if (checkNumOfOperands(operand1, operand2, operand3) > expectedOperands) {
            reportError(fileName, 1, orgLine);
            return;
        } else if (checkNumOfOperands(operand1, operand2, operand3) < expectedOperands) {
            reportError(fileName, 2, orgLine);
            return;
        }

        /* Generating the code machine according to the num of expected operands of current instruction */
        switch (expectedOperands) {
            case 0:
                processInstructionWith0Operands(fileName, copiedLine, opCode);
                break;
            case 1:
                processInstructionWith1Operands(fileName, copiedLine, opCode, operand1, addressingMethod1);
                break;
            case 2:
                processInstructionWith2Operands(fileName, copiedLine, opCode, operand1, addressingMethod1, addressingMethod2, operand2);
                break;
        }
    } else /* Instruction isn't exist in the instruction table */
        reportError(fileName, 7, orgLine);
}

void processDirective(const char *fileName, char *line, char *orgLine) {
    char copiedLine [MAX_LINE_LENGTH]; /* Create an array to hold the copy of the line */
    strcpy(copiedLine, line); /* Make a copy of the original line */

    /* Tokenizing parameters according the last source of line */
    char *directive;
    char *arguments;
    tokenizeArguments(line, &directive, &arguments);

    /*  Missing operands */
    if (arguments == NULL)
        reportError(fileName, 2, copiedLine);

    /* ".data" directive */
    if (strcmp(directive, ".data") == 0) {
        processDataDirective(fileName, copiedLine, arguments);
        /* If processing directive through label declaration, send copiedLine as a parameter to checkCommas,
         otherwise send orgLine as a parameter */
        if(directFlag)
            checkCommas(fileName, copiedLine);
        else
            checkCommas(fileName, orgLine);
    } else if (strcmp(directive, ".string") == 0) {         /* ".string" directive */
        processStringDirective(fileName, copiedLine, arguments);
    } else if (strcmp(directive, ".entry") == 0) {         /* ".entry" directive */
        processEntryDirective(fileName, copiedLine, arguments);
    } else if (strcmp(directive, ".extern") == 0) { /* ".extern" directive */
        processExternDirective(fileName, copiedLine, arguments);
    } else /* Invalid directive */
        reportError(fileName, 8, copiedLine);
}

void firstPass(FILE *file, const char *fileName) {
    address = INITIAL_ADDRESS_VALUE; /* Initializing address to it's initial value */
    char line[MAX_LINE_LENGTH]; /* Line to process */
    char copiedLine[MAX_LINE_LENGTH]; /* The copy of the line being processed */
    char orgLine[MAX_LINE_LENGTH]; /* The original line being processed  */

    while (fgets(line, sizeof(line), file)) {
        /* Remove newline/carriage return character from the end of the line */
        line[strcspn(line, "\r\n")] = '\0';

        /* Avoid double increment for line value. Increment line value only if first pass isn't finished yet */
        if (!endFirstPassFlag)
            lineNum++;

        /* Skip commented lines */
        if (line[0] == ';')
            continue;

        /* Make a copies of the line being processed */
        strcpy(copiedLine, line);
        strcpy(orgLine, line);
        directFlag = 0;

        /* Report error for overflow line */
        if(strlen(line) > MAX_LINE_LENGTH) {
            reportError(fileName, 15, copiedLine);
            continue;
        }

        char *token = strtok(line, " \n\t");
        /* Skip empty line */
        if (token == NULL || token[0] == ';')
            continue;

        /* Label declaration has been found */
        if (isLabelDeclaration(fileName, token)) {
            /* Process label declaration */
            processLabelDeclaration(fileName, copiedLine);
        } else if (isDirectiveDeclaration(token)) {     /* Directive declaration has been found */
            directFlag = 1;
            /* Process directive */
            processDirective(fileName, copiedLine, NULL);
        } else { /* Line is instruction */
            directFlag = 1;
            /* Process instruction */
            processInstruction(fileName, copiedLine, orgLine);
        }
    }
    /* Raising a flag that notates the end of the first passage */
    endFirstPassFlag = 1;
}

void secondPass(FILE *file, const char *fileName) {
    firstPass(file, fileName);
}

void produceObjectFile(FILE *file) {
    int i = 0;
    for (; i < address - INITIAL_ADDRESS_VALUE; ++i) {
        fprintf(file, "%s\n", convertToBase64(codeWordTable[i].binaryCode));
    }
}
