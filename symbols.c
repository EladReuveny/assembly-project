#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"
#include "symbols.h"
#include "analyze.h"

typedef struct Symbol {
    char name[MAX_LABEL_LENGTH];
    int value;
    int isEntry;
    int isExtern;
    struct Symbol* next;
} Symbol;

Symbol* symbolTable = NULL;
Symbol* externSymbolTable = NULL;

void addToSymbolTable(const char *fileName, char *name, int value, int isEntry, int isExtern) {
    /* Create dynamic memory space for new symbol */
    Symbol* newSymbol = (Symbol*)malloc(sizeof(Symbol));

    /* Report memory allocation has been failed for new symbol */
    if(newSymbol == NULL) {
        reportError(fileName, 12, " ");
        return;
    }

    /* Set new symbol parameters */
    strcpy(newSymbol->name, name);
    newSymbol->value = value;
    newSymbol->isEntry = isEntry;
    newSymbol->isExtern = isExtern;
    newSymbol->next = NULL;

    /* Symbol table is empty */
    if (symbolTable == NULL) {
        symbolTable = newSymbol;
    } else {
        Symbol* current = symbolTable;

        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newSymbol;
    }
}

int isSymbolExist(char* symbolName) {
    Symbol* current = symbolTable;

    while (current != NULL) {
        /* symbolName has been found in the symbol table */
        if (strcmp(current->name, symbolName) == 0)
            return true;
        current = current->next;
    }
    return false;  /* Symbol  hasn't been found */
}

int getSymbolValue(const char* symbolName) {
    Symbol* current = symbolTable;

    while (current != NULL) {
        /* symbolName has been found in the symbol table */
        if (strcmp(current->name, symbolName) == 0)
            return current->value;
        current = current->next;
    }
    return -1;  /* Symbol  hasn't been found */
}

int getSymbolType(const char *symbolName) {
    Symbol* current = symbolTable;

    while (current != NULL) {
        /* symbolName has been found in the symbol table */
        if (strcmp(current->name, symbolName) == 0) {
            if (!current->isExtern) /* Current symbol isn't marked as extern point */
                return 2; /* Entry */
            else
                return 1; /* Extern */
        }
        current = current->next;
    }
    return -1;  /* Symbol  hasn't been found */
}

void updateSymbolTable(char* name, int value) {
    Symbol* symbol = symbolTable;

    while (symbol != NULL) {
        /* symbol has been found in the symbol table */
        if(strcmp(symbol->name, name) == 0) {
            symbol->value = value;
            return;
        }
        symbol = symbol->next;
    }
}

void setEntrySymbol(char *symbolName) {
    Symbol *current = symbolTable;

    while (current != NULL) {
        /* symbolName has been found in the symbol table */
        if (strcmp(current->name, symbolName) == 0) {
            current->isEntry = 1;
            return;
        }
        current = current->next;
    }
}

void setExternSymbol(char *symbolName) {
    Symbol *current = symbolTable;

    while (current != NULL) {
        /* symbolName has been found in the symbol table */
        if (strcmp(current->name, symbolName) == 0) {
            current->isExtern = 1;
            return;
        }
        current = current->next;
    }
}

void addToExternSymbolTable(const char *fileName, const char *name, int value) {
    /* Create dynamic memory space for new symbol */
    Symbol* newSymbol = (Symbol*)malloc(sizeof(Symbol));

    /* Report memory allocation has been failed for new symbol */
    if(newSymbol == NULL) {
        reportError(fileName, 12, " ");
        return;
    }

    /* Set new symbol parameters */
    strcpy(newSymbol->name, name);
    newSymbol->value = value;
    newSymbol->isEntry = 0;
    newSymbol->isExtern = 1;
    newSymbol->next = NULL;

    /* Extern symbol table is empty */
    if (externSymbolTable == NULL) {
        externSymbolTable = newSymbol;
    } else {
        Symbol* current = externSymbolTable;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newSymbol;
    }
}

int hasEntry() {
    Symbol *current = symbolTable;

    /* Search for entry point symbol */
    while (current != NULL) {
        /* Entry point symbol has been found in the symbol table */
        if (current->isEntry)
            return true;
        current = current->next;
    }
    return false; /* Entry point symbol hasn't been found in the symbol table */
}

int hasExtern() {
    Symbol *current = symbolTable;

    /* Search for extern point symbol */
    while (current != NULL) {
        /* Extern point symbol has been found in the symbol table */
        if (current->isExtern)
            return true;
        current = current->next;
    }
    return false; /* Extern point symbol hasn't been found in the symbol table */
}

int isExtern(const char *name) {
    Symbol *symbol = symbolTable;

    while (symbol != NULL) {
        /* symbol has been found in the symbol table */
        if (strcmp(symbol->name, name) == 0 && symbol->isExtern)
            return true;
        symbol = symbol->next;
    }
    return false; /* symbol hasn't been found in the symbol table */
}

int isEntry(char *name) {
    Symbol *symbol = symbolTable;

    while (symbol != NULL) {
        /* symbol has been found in the symbol table and is marked as an entry point symbol */
        if (strcmp(symbol->name, name) == 0 && symbol->isEntry)
            return true;
        symbol = symbol->next;
    }
    return false; /* symbol isn't marked as an entry point symbol */
}

void produceEntryFile(FILE* file) {
    Symbol *symbol = symbolTable;

    while (symbol != NULL) {
        /* Current symbol is marked as an entry point symbol, so write it's name and value into the entry file*/
        if (symbol->isEntry)
            fprintf(file, "%s %d\n", symbol->name, symbol->value);
        symbol = symbol->next;
    }
}

void produceExternFile(FILE* file) {
    Symbol *symbol = externSymbolTable;

    while (symbol != NULL) {
        /* Write it's name and value into the extern file*/
        fprintf(file, "%s %d\n", symbol->name, symbol->value);
        symbol = symbol->next;
    }
}

void freeSymbolTable() {
    Symbol *current = symbolTable;

    /* Release each symbol node of symbol table out of the memory */
    while (current != NULL) {
        Symbol *temp = current;
        current = current->next;
        free(temp);
    }
    symbolTable = NULL;
}

void freeExternSymbolTable() {
    Symbol *current = externSymbolTable;

    /* Release each symbol node of extern symbol table out of the memory */
    while (current != NULL) {
        Symbol *temp = current;
        current = current->next;
        free(temp);
    }
    externSymbolTable = NULL;
}
