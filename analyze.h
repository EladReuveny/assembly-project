#ifndef ANALYZE_H
#define ANALYZE_H

/**
 * @file analyze.h
 * @brief Definitions and functions related processing and analyzing the assembly file..
 */

/**
 * Current address.
 */
extern int address;

/**
 * Current number of line in the file.
 */
extern int lineNum;

/**
 * @brief The directFlag determines the tokenization order.
 *
 * A flag that notates whether the current line is processed directly through process directive/instruction,
 * so that the strtok function would know where exactly start tokenizing from - from last location who was tokenized/
 * from the start of the current line.
 *
 */
extern int directFlag;

/**
 * A flag that notates the end of the first passage, so that all symbols attributes are now known.
 */
extern int endFirstPassFlag;

/**
 * A flag to notify that at least one error has been found in the source file, so that the output files couldn't be produced.
 */
extern int errorFlag;

/**
 * @brief Perform the first pass of the assembly process.
 *
 * The first pass scans the input file and constructs the symbol table based on labels and directives.
 * It also processes and validates instructions, directives, and labels encountered during the pass, and generates
 * partial of the machine code.
 *
 * @param fileName The name of the file being processed.
 * @param file The input file to be processed.
 */
void firstPass(FILE *file, const char *fileName);

/**
 * @brief Perform the second pass of the assembly process.
 *
 * The second pass generates the machine code and produces the object file based on the constructed symbol table.
 *
 * @param file The input file to be processed.
 * @param fileName The name of the file being processed.
 */
void secondPass(FILE *file, const char *fileName);

/**
 * @brief Process a label declaration in the assembly code.
 *
 * This function processes a label declaration encountered during the assembly process.
 * It adds the label to the symbol table with the current address.
 *
 * @param fileName The name of the file being processed.
 * @param line The line containing the label declaration.
 */
void processLabelDeclaration(const char *fileName, char *line);

/**
 * @brief Process a directive in the assembly code.
 *
 * This function processes a directive encountered during the assembly process.
 * It handles directives such as .data, .string, .entry, and .extern.
 *
 * @param fileName The name of the file being processed.
 * @param line The line containing the directive.
 * @param orgLine The original line being processed.
 */
void processDirective(const char *fileName, char *line, char *orgLine);

/**
 * @brief Process an instruction in the assembly code.
 *
 * This function processes an instruction encountered during the assembly process.
 * It handles instructions with different addressing modes and generates machine code.
 *
 * @param fileName The name of the file being processed.
 * @param line The instruction line.
 * @param orgLine The original line being processed.
 */
void processInstruction(const char *fileName, char *line, const char *orgLine);

/**
 * @brief Produce the object file from the machine code.
 *
 * This function writes the machine code to the output file in base64 format,
 * producing the object file with the machine code for the assembly program.
 *
 * @param file The output file to write the machine code.
 */
void produceObjectFile(FILE* file);

#endif