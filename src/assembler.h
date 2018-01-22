#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sourceCode.h"
#include "assembledCode.h"

struct Assembler
{
    struct SourceCode source_code;
    uint32_t location_counter;
    struct AssembledCode assembled_code;
};

int assemblerInitialise(struct Assembler *assembler, char *source_file_name, char* binary_file_name);

int assemblerAssemble(struct Assembler *assembler);

void assemblerDestroy(struct Assembler *assembler);

void assemblerParseLine(const char* line);

#endif
