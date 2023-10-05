#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"
#include "macro.h"

typedef struct Macro {
    char name[MAX_MACRO_NAME_LENGTH];
    char content[MAX_LINE_LENGTH];
    Macro *next;
} Macro;

int hasMacro(FILE *file) {
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {

        char *token = strtok(line, " ,\t\n");
        if (token != NULL && (strncmp(token, "mcro", 4) == 0)) {
            return true;
        }
    }
    return false;
}

int isMacro(Macro *macroTable, char *token) {
    if (token == NULL || macroTable == NULL) {
        return false;
    }

    Macro *macro = macroTable;
    while (macro != NULL) {
        if (strcmp(token, macro->name) == 0) {
            return true;
        }
        macro = macro->next;
    }
    return false;
}

void addMacro(Macro **macroTable, Macro *newMacro) {
    if (*macroTable == NULL) {
        *macroTable = newMacro;
    } else {
        Macro *cur = *macroTable;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = newMacro;
    }
}

void writeMacro(FILE *postSpanning, Macro *macroTable, char *token) {
    if (macroTable == NULL) {
        return;
    }

    Macro *macro = macroTable;
    while (macro != NULL) {
        if (strcmp(token, macro->name) == 0) {
            /* Write the macro content to the output file */
            fputs(macro->content, postSpanning);
            break;
        }
        macro = macro->next;
    }
}

void createMacro(FILE *source, const char *fileName, char *line, char *token, Macro *newMacro) {
    char copiedLine[MAX_LINE_LENGTH]; /* Create an array to hold the copy of the line */
    strcpy(copiedLine, line);         /* Make a copy of the original line */

    token = strtok(NULL, " ,\t\n");

    /* Report error if macro's name is missing. */
    if (token == NULL) {
        reportError(fileName, 12, copiedLine);
        return;
    }

    
    /* Report error if macro's name is used as a reserved keyword (directive/instruction). */
    if (strncmp(token, ".string", 7) == 0 || strncmp(token, ".data", 5) == 0 ||
        strncmp(token, ".entry", 6) == 0 || strncmp(token, ".extern", 7) == 0 || isInstructionExist(token)) {
        reportError(fileName, 13, copiedLine);
        return;
    }

    strcpy(newMacro->name, token); /* Set macro's name */
    token = strtok(NULL, " ,\t\n");

    /* Report error if there's another operand after declaring the macro's name. */
    if (token != NULL) {
        reportError(fileName, 14, copiedLine);
	return;
    }

    /* Get next line to complete macro definition */
    fgets(copiedLine, sizeof(copiedLine), source);

    newMacro->content[0] = '\0'; /* Initialize content buffer */
    newMacro->next = NULL;

    /* Loop to read and concatenate lines until "endmcro" is encountered */
    while (strncmp(copiedLine, "endmcro", 7) != 0) {
	lineNum++; /* Update number of line */

        /* Concatenate line to content */
        strcat(newMacro->content, copiedLine);
        fgets(copiedLine, sizeof(copiedLine), source);
    }

    lineNum++; /* Update number of line */

    strcpy(line, copiedLine); /* Keep last line which has been read */
    token = strtok(copiedLine, " ,\t\n");
    token = strtok(NULL, " ,\t\n");
    /* Report an error if there's another operand after declaring the end of the macro definition. */
    if (token != NULL) {
        reportError(fileName, 23, line);
    }
}


void macroSpanning(FILE *source, FILE *postSpanning, const char *fileName) {
    char line[MAX_LINE_LENGTH];
    char copiedLine[MAX_LINE_LENGTH]; /* Copy of the line */
    char *token; /* Used to tokenize the line being processed */

    fseek(source, 0, SEEK_SET); /* Reset file pointer to the beginning */

    Macro *macroTable = NULL; /* Head pointer for the macro table */

    /* Process each line of the file */
    while (fgets(line, sizeof(line), source)) {
        lineNum++; /* Update number of line */
        strcpy(copiedLine, line); /* Make a copy of the line */
        token = strtok(line, " ,\t\n"); /* Tokenizing current line */

        /* Skip commented line or new lines */
        if (token == NULL || token[0] == ';' || strcmp(copiedLine, "\n") == 0)
            continue;

            /* Macro declaration */
        else if (strncmp(line, "mcro", 4) == 0) {
            Macro *newMacro = (Macro *) malloc(sizeof(Macro));

            /* Report memory allocation has been failed for new macro */
            if (newMacro == NULL) {
                reportError(fileName, 12, copiedLine);
                return;
            }

            /* Create and add macro to the macro table */
            createMacro(source, fileName, copiedLine, token, newMacro);

            /* Skip to the next line if error has been found while creating the macro */
            if (errorFlag)
                continue;

            addMacro(&macroTable, newMacro);
        } else if (isMacro(macroTable, token)) /* Macro found */
            /* Write existed macro to pre assembler file with the ending of ".am" */
            writeMacro(postSpanning, macroTable, token);
        else     /* Write the line as it is */
            fputs(copiedLine, postSpanning);
    }

    freeMacroTable(macroTable); /* Reset macro table */
}

void freeMacroTable(Macro *macroTable) {
    Macro *currentMacro = macroTable;

    /* Release each node of macros table */
    while (currentMacro != NULL) {
        Macro *temp = currentMacro;
        currentMacro = currentMacro->next;
        free(temp);
    }
}
