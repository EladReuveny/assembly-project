#ifndef  SYMBOLS_H
#define SYMBOLS_H

/**
 * @file symbols.h
 * @brief Definitions and functions related to symbol table and symbols.
 */

/**
 * @struct Symbol
 * @brief Structure to represent a symbol in the symbol table.
 *
 * This structure holds information about a symbol, including its name, value,
 * whether it is an entry point, whether it is external, and a pointer to the next symbol.
 */
typedef struct Symbol Symbol;

/**
 * @brief Pointer to the symbol table.
 *
 * This pointer points to the head of the symbol table, which is a linked list of symbols.
 * The symbol table stores information about symbols encountered during the assembly process.
 * Each symbol has a name, a value (address), and flags to indicate if it's an entry point or external.
 */
extern Symbol* symbolTable;

/**
 * @brief Pointer to the extern symbol table.
 *
 * This pointer points to the head of the extern symbol table, which is a linked list of symbols.
 * The extern symbol table stores information about symbols encountered during the assembly process.
 * Each symbol has a name, a value (address), and flags to indicate if it's an entry point or external.
 */
extern Symbol* externSymbolTable;

/**
 * @brief Add a new symbol to the symbol table.
 *
 * This function adds a new symbol to the symbol table with the given attributes.
 *
 * @param fileName The name of the file being processed.
 * @param name The name of the symbol.
 * @param value The value (address) of the symbol.
 * @param isEntry Flag indicating if the symbol is an entry point (true) or not (false).
 * @param isExtern Flag indicating if the symbol is external (true) or not (false).
 */
void addToSymbolTable(const char *fileName, char *name, int value, int isEntry, int isExtern);

/**
 * @brief Check if a symbol with the given name exists in the symbol table.
 *
 * This function checks if a symbol with the given name exists in the symbol table.
 *
 * @param symbolName The name of the symbol to check.
 * @return True if the symbol exists, false otherwise.
 */
int isSymbolExist(char* symbolName);

/**
 * @brief Get the value (address) of a symbol with the given name.
 *
 * This function returns the value (address) of a symbol with the given name from the symbol table.
 *
 * @param symbolName The name of the symbol.
 * @return The value (address) of the symbol, or -1 if the symbol isn't found.
 */
int getSymbolValue(const char* symbolName);

/**
 * @brief Get the type of a symbol in the symbol table.
 *
 * This function returns the type of a symbol in the symbol table, which can be 1 (extern) or 2 (entry).
 *
 * @param symbolName The name of the symbol.
 * @return The type of the symbol (1 for extern, 2 for entry), or -1 if the symbol is not found.
 */
int getSymbolType(const char* symbolName);

/**
 * Updates the value of an existing symbol in the symbol table with the given name.
 *
 * @param name  The name of the symbol to update.
 * @param value The new value for the symbol.
 */
void updateSymbolTable(char *name, int value);

/**
 * @brief Sets the entry attribute for a symbol with the given name in the symbol table.
 *
 * This function sets the entry attribute of a symbol with the specified name to 1,
 * indicating that it is an entry point in the assembly program.
 *
 * @param symbolName The name of the symbol to set as an entry point.
 */
void setEntrySymbol(char *symbolName);

/**
 * @brief Sets the extern attribute for a symbol with the given name in the symbol table.
 *
 * This function sets the extern attribute of a symbol with the specified name to 1,
 * indicating that it is an external symbol in the assembly program.
 *
 * @param symbolName The name of the symbol to set as an external symbol.
 */
void setExternSymbol(char *symbolName);

/**
 * Adds a new symbol to the extern symbol table with the given name and value.
 *
 * @param fileName The name of the file being processed.
 * @param name  The name of the symbol to add.
 * @param value The value of the symbol.
 */
void addToExternSymbolTable(const char *fileName, const char *name, int value);

/**
* @brief Check if the symbol table contains any entry symbols.
*
* @return true if the file has an entry point symbol, false otherwise.
*/
int hasEntry();

/**
 * @brief Check if the symbol table contains any external symbols.
 *
 * @return true if the symbol table has an external symbol, false otherwise.
 */
int hasExtern();

/**
 * @brief Checks if a symbol with the given name exists in the symbol table and if it is marked as an external symbol.
 *
 * @param name The name of the symbol to check.
 * @return True if the symbol with the given name is marked as an external symbol, false otherwise.
 */
int isExtern(const char *name);

/**
 * @brief Checks if a symbol with the given name exists in the symbol table and if it is marked as an entry symbol.
 *
 * @param name The name of the symbol to check.
 * @return True if the symbol with the given name is marked as an entry symbol, false otherwise.
 */
int isEntry(char *name);

/**
 * @brief Produce the entry file with entry point symbols.
 *
 * This function writes the entry point symbols to the output file,
 * producing the entry file for the assembly program.
 *
 * @param file The output file to write the entry point symbols.
 */
void produceEntryFile(FILE* file);

/**
 * @brief Produce the extern file with external symbols.
 *
 * This function writes the external symbols to the output file,
 * producing the extern file for the assembly program.
 *
 * @param file The output file to write the external symbols.
 */
void produceExternFile(FILE* file);

/**
 * @brief Frees the memory used by the symbol table.
 */
void freeSymbolTable();

/**
 * @brief Frees the memory used by the external symbol table.
 */
void freeExternSymbolTable();

#endif
