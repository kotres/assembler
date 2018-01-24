#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

#include "sourceCode.h"
#include "cleanCode.h"

struct Assembler
{
    struct SourceCode source_code;
    struct CleanCode clean_code;
    uint32_t location_counter;

};

int assemblerInitialise(struct Assembler *assembler, char *source_file_name);

int assemblerAssemble(struct Assembler *assembler);

void assemblerDestroy(struct Assembler *assembler);

/*int assemblerParseLine(struct Assembler *assembler, char* line);

void assemblerCleanLine(char *line);

void assemblerRemoveWhitespace(char *line);

void assemblerConvertToUpperCase(char *line);

int assemblerDetectInstruction(char *line);*/

#endif
