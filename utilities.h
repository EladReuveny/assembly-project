#ifndef UTILITIES_H
#define UTILITIES_H

/**
 * @file utilities.h
 * @brief Functions to facilitate processing the source file.
 */

/**
 * @brief Check if a character is an alphabetic character (A-Z or a-z).
 *
 * @param c The character to check.
 * @return True if the character is alphabetic, false otherwise.
 */
int isCharacter(char c);

/**
 * @brief Check if a line is a label declaration.
 *
 * This function checks if a line in the assembly code is a label declaration.
 *
 * @param fileName The name of the file being processed.
 * @param line The line to check.
 * @return True if the line is a label declaration, false otherwise.
 */
int isLabelDeclaration(const char *fileName, char *line);

/**
 * Checks if a given string is a directive declaration.
 *
 * @param directive The string to be checked.
 * @return True if the string is a directive declaration (starts with a dot - '.'), otherwise false.
 */
int isDirectiveDeclaration(char *directive);

/**
 * @brief Check if a string represents a numeric value (integer).
 *
 * @param operand The string to check.
 * @return True if the string represents a numeric value, false otherwise.
 */
int isNumeric(char *operand);

/**
 * @brief Gets the register number corresponding to the given operand.
 *
 * @param operand The operand to check for the register.
 * @return The register number (0 to 7) if the operand is a valid register, or -1 if the operand is invalid.
 */
int getRegister(const char *operand);

/**
 * @brief Get the addressing method of an operand.
 *
 * This function determines the addressing method of an operand based on its syntax.
 * It can return METHOD_IMMEDIATE, METHOD_DIRECT_REGISTER, or METHOD_DIRECT.
 *
 * @param operand The operand to determine the addressing method for.
 * @return The addressing method of the operand.
 */
int getAddressingMethod(char *operand);

/**
 * @brief Initializes the memory used for the assembler, resetting relevant variables and freeing allocated memory.
 */
void initializeMemory();

/**
 * @brief Reports an error encountered during the assembly process.
 *
 * This function prints a certain error which encountered during process a line. Also, this function raises the
 * errorFlag to notify that at least one error has been found in the source file.
 *
 * @param fileName The name of the file being processed.
 * @param errorCode The error code representing the specific type of error.
 * @param errorMessage The error message representing the specific line the error has been occurred at.
 */
void reportError(const char *fileName, int errorCode, const char *errorMessage);

/**
 * @brief Counts the number of non-null operands among the given operands.
 *
 * This function counts the number of non-null operands among the provided
 * operand pointers. It checks each operand pointer and increments the count
 * for each non-null operand. The function returns the total count of
 * non-null operands.
 *
 * @param operand1 Pointer to the first operand.
 * @param operand2 Pointer to the second operand.
 * @param operand3 Pointer to the third operand.
 * @return The number of non-null operands among the given operands.
 */
int checkNumOfOperands(const char *operand1, const char *operand2, const char *operand3);

/**
 * Checks if the current address is a valid address within the code word table.
 *
 * @return True if the current address is valid, false otherwise.
 */
int isValidAddress();

/**
 * Tokenizes the arguments in the given line and returns the directive and arguments separately.
 * The directFlag determines the tokenization order.
 *
 * @param line The input line to be tokenized.
 * @param directive Pointer to a char pointer to store the directive.
 * @param arguments Pointer to a char pointer to store the arguments.
 */
void tokenizeArguments(char *line, char **directive, char **arguments);

/**
  * Checks for comma-related errors in a given line.
  *
  * @param fileName    The name of the file being checked.
  * @param line        The line to be checked for comma errors.
  */
void checkCommas(const char *fileName, char *line);

/**
 * Processes the ".data" directive and adds the binary data to the code word table.
 *
 * @param fileName The name of the source file being processed.
 * @param copiedLine A copy of the original line for error reporting.
 * @param arguments The arguments of the ".data" directive to be processed.
 */
void processDataDirective(const char *fileName, const char *copiedLine, char *arguments);

/**
 * Processes the ".string" directive and adds the binary data to the code word table.
 *
 * @param fileName The name of the source file being processed.
 * @param copiedLine A copy of the original line for error reporting.
 * @param arguments The arguments of the ".string" directive to be processed.
 */
void processStringDirective(const char *fileName, const char *copiedLine, char *arguments);

/**
 * Processes the ".entry" directive and adds the entry symbol(s) to the symbol table.
 *
 * @param fileName The name of the source file being processed.
 * @param copiedLine A copy of the original line for error reporting.
 * @param arguments The arguments of the ".entry" directive to be processed.
 */
void processEntryDirective(const char *fileName, const char *copiedLine, char *arguments);

/**
 * Processes the ".extern" directive and adds the external symbol(s) to the symbol table.
 *
 * @param fileName The name of the source file being processed.
 * @param copiedLine A copy of the original line for error reporting.
 * @param arguments The arguments of the ".extern" directive to be processed.
 */
void processExternDirective(const char *fileName, const char *copiedLine, char *arguments);

/**
 * Process an instruction with zero operands.
 *
 * @param fileName The name of the source file.
 * @param copiedLine The copied line from the source file.
 * @param opCode The opcode of the instruction.
 */
void processInstructionWith0Operands(const char *fileName, const char *copiedLine, const char *opCode);

/**
 * Process an instruction with one operand.
 *
 * @param fileName The name of the source file.
 * @param copiedLine The copied line from the source file.
 * @param opCode The opcode of the instruction.
 * @param operand1 The first operand.
 * @param addressingMethod1 The addressing method for the first operand.
 */
void processInstructionWith1Operands(const char *fileName, const char *copiedLine, const char *opCode
        , const char *operand1, int addressingMethod1);

/**
 * Process an instruction with two operands.
 *
 * @param fileName The name of the source file.
 * @param copiedLine The copied line from the source file.
 * @param opCode The opcode of the instruction.
 * @param operand1 The first operand.
 * @param addressingMethod1 The addressing method for the first operand.
 * @param addressingMethod2 The addressing method for the second operand.
 * @param operand2 The second operand.
 */
void
processInstructionWith2Operands(const char *fileName, const char *copiedLine, const char *opCode, const char *operand1
        , int addressingMethod1, int addressingMethod2, const char *operand2);

#endif