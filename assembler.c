/**
 * @file assembler.c
 * @author Elad Reuveny
 * @details This program is an assembler that translates assembly language source code
 * into machine code. It supports macros,  symbols, and generates output files including the object code,
 * entry symbols, and extern symbols.
 * @example Run ./assembler file1, file2, file3, ..., etc             (on command line) to execute this program.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "symbols.h"
#include "utilities.h"
#include "analyze.h"
#include "macro.h"

int main(int argc, char *argv[]) {
    /* Finish the program when no source file provided */
    if (argc < 2) {
        reportError(NULL, 4, *argv);
        return EXIT_FAILURE;
    }

    /* Setting different types of files */
    FILE *file;
    FILE *amFile;
    FILE *obFile;
    FILE *entFile;
    FILE *extFile;

    int i;
    for (i = 1; i < argc; i++) {
        /* Setting memory for files names and initializing memory*/
        char asFileName[MAX_LINE_LENGTH];
        char amFileName[MAX_LINE_LENGTH];
        char obFileName[MAX_LINE_LENGTH];
        char entFileName[MAX_LINE_LENGTH];
        char extFileName[MAX_LINE_LENGTH];
        initializeMemory();

        /* Open new assembly file with ".as" ending */
        strcat(strcpy(asFileName, argv[i]), ".as");
        file = fopen(asFileName, "r");

        /* File couldn't being found/opened  */
        if (file == NULL) {
            reportError(argv[i], 5, argv[i]);
            continue;
        }

        /* File has at least one macro declaration. Assuming the .am file would be opened even thou
          there's an error has been found in the source file, but the output files won't be produced anyway */
        if (hasMacro(file)) {
            /* Open new assembly file with ".am" ending */
            strcat(strcpy(amFileName, argv[i]), ".am");
            amFile = fopen(amFileName, "a");

            /* File couldn't being found/opened */
            if (amFile == NULL) {
                reportError(NULL, 5, argv[i]);
                continue;
            }

            /* Span macros and write their definition into the amFile */
            macroSpanning(file, amFile, argv[i]);
            fclose(amFile); /* Close the amFile after writing macro data */
            file = fopen(amFileName, "r"); /* Reopen the file for the first and second pass */
        } else /* File doesn't have any macro declaration */
            file = fopen(asFileName, "r"); /* Reopen the file for the first and second pass */

        /* Checking for errors after pre assembly process.
          It wasn't clear enough if after the pre assembly process, the source file needs to be skipped,
          so I've assumed to skip to the next source file right after.*/
        if(errorFlag) {
            printf("-------------------------------------------------------------------------------\n");
            printf("***The assembler couldn't process %s file cause at least one error has been found***\n\n", argv[i]);
	    printf("-------------------------------------------------------------------------------\n");
            continue;
        }

        /* Executing first and second passes */
        firstPass(file, argv[i]);
        fseek(file, 0, SEEK_SET); /* Reset file pointer before the second pass */
        secondPass(file, argv[i]);

        /* Checking for errors after first and second passes  */
        if(errorFlag) {
            printf("-------------------------------------------------------------------------------\n");
            printf("***The assembler couldn't process %s file cause at least one error has been found***\n\n", argv[i]);
	    printf("-------------------------------------------------------------------------------\n");
            continue;
        }

       /* Open object file for the machine code */
        strcat(strcpy(obFileName, argv[i]), ".ob");
        obFile = fopen(obFileName, "a");

        /* File couldn't being found/opened */
        if (obFile == NULL) {
            reportError(argv[i], 5, argv[i]);
            continue;
        }

        /* Write machine code into the object file */
        produceObjectFile(obFile);
        fclose(obFile);

        /* File has at least one entry point declaration  */
        if (hasEntry(file)) {
            /* Open entry file for the entry symbols  */
            strcat(strcpy(entFileName, argv[i]), ".ent");
            entFile = fopen(entFileName, "a");

            /* File couldn't being found/opened  */
            if (entFile == NULL) {
                reportError(argv[i], 5, argv[i]);
                continue;
            }

            /* Write entry point symbols into the entry file */
            produceEntryFile(entFile);
            fclose(entFile);
        }

        /* File has at least one extern point declaration  */
        if (hasExtern(file)) {
            /* Open extern file for the extern symbols  */
            strcat(strcpy(extFileName, argv[i]), ".ext");
            extFile = fopen(extFileName, "a");

            /* File couldn't being found/opened  */
            if (extFile == NULL) {
                reportError(argv[i], 5, argv[i]);
                continue;
            }

            /* Write extern point symbols into the extern file */
            produceExternFile(extFile);
            fclose(extFile);
        }

        fclose(file); /* Closing file */
    }

    return EXIT_SUCCESS;
}
