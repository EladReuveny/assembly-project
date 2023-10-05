#ifndef MACRO_H
#define MACRO_H

/**
 * @file macro.h
 * @brief Definitions and functions related to macros.
 */

/**
 * Represents a macro structure.
 */
typedef struct Macro Macro;

/**
 * Checks if the given file contains any macro definitions.
 *
 * @param file The input file to check for macro definitions.
 * @return 1 if the file has at least one macro, otherwise 0.
 */
int hasMacro(FILE *file);

/**
 * Adds a new macro to the macro table.
 *
 * @param macroTable A pointer to the pointer to the macro table.
 * @param newMacro The new macro to add to the macro table.
 */
void addMacro(Macro **macroTable, Macro *newMacro);

/**
 * Creates a macro from the given source file, line, and token.
 *
 * @param source The source file containing the macro definition.
 * @param fileName The name of the source file (used for error reporting).
 * @param line The line of the macro definition.
 * @param token The token representing the macro name.
 * @param newMacro The newly created macro structure to store the macro information.
 */
void createMacro(FILE *source, const char *fileName, char *line, char *token, Macro *newMacro);

/**
 * Checks if the given token is a macro.
 *
 * @param macroTable The macro table containing the macros to search for the given token.
 * @param token The token to check for macro existence.
 * @return 1 if the token is a macro, otherwise 0.
 */
int isMacro(Macro *macroTable, char *token);

/**
 * Processes the macros spanning multiple lines in the source file and writes the result to the postSpanning file.
 *
 * @param source The source file containing the macros spanning multiple lines.
 * @param postSpanning The output file where the processed macros are written.
 * @param fileName The name of the source file (used for error reporting).
 */
void macroSpanning(FILE *source, FILE *postSpanning, const char *fileName);

/**
 * Writes the content of a macro to the output file.
 * If a macro with the given name is found in the macro table, its content is written to the output file.
 *
 * @param postSpanning The file pointer to the output file where the macro content will be written.
 * @param macroTable The macro table containing the macros to search for the given token.
 * @param token The name of the macro to be written.
 */
void writeMacro(FILE *postSpanning, Macro *macroTable, char *token);

/**
 * Frees the memory allocated for the macro table.
 *
 * @param macroTable The macro table to be freed.
 */
void freeMacroTable(Macro *macroTable);

#endif
