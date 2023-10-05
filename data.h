#ifndef DATA_H
#define DATA_H

/**
 * @file data.h
 * @brief Definitions of constant macros to facilitate maintaining the project more clearly.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analyze.h"
#include "macro.h"
#include "instructions.h"
#include "symbols.h"
#include "machinecode.h"
#include "utilities.h"

/**
 * Valid line length.
 */
#define MAX_LINE_LENGTH 80

/**
 * Valid macro name length.
 */
#define MAX_MACRO_NAME_LENGTH 20

/**
 * Valid label length.
 */
#define MAX_LABEL_LENGTH 31

/**
 * Length of instructions table.
 */
#define INSTRUCTIONS_LENGTH 16

/**
 * Initial value of address in the memory.
 */
#define INITIAL_ADDRESS_VALUE 100

/**
 * Length of available machine code in the memory.
 */
#define MAX_CODE_WORD_TABLE_SIZE 1024

/**
 * Mark 1 as true.
 */
#define true 1

/**
 * Mark 0 as false .
 */
#define false 0

/**
 * Immediate addressing mark.
 */
#define METHOD_IMMEDIATE 1

/**
 * Direct addressing mark.
 */
#define METHOD_DIRECT 3

/**
 * Direct register addressing mark.
 */
#define METHOD_DIRECT_REGISTER 5

#endif
