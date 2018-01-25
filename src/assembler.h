#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

#include "sourceCode.h"
#include "label.h"

#define MAXIMUM_LINE_LENGTH 256

struct Assembler
{
    struct SourceCode *source_code;
    uint32_t location_counter;
    struct Label *labels;
};

void assemblerInitialise(struct Assembler *assembler);

int assemblerAssemble(struct Assembler *assembler,const char *source_file_name);

int assemblerLoadSourceCode(struct Assembler *assembler,const char *source_file_name);

int assemblerFindLabels(struct Assembler *assembler);

int assemblerDecodeSourceCode(struct Assembler *assembler);

int assemblerParseLine(struct Assembler *assembler, struct SourceCode **iterator_pointer);

void assemblerDestroy(struct Assembler *assembler);

#endif
