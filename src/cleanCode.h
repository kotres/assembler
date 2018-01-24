#ifndef CLEAN_CODE_H
#define CLEAN_CODE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

#include "sourceCode.h"

struct CleanCode
{
    char** data;
    unsigned int size;
};

int cleanCodeInitialize(struct CleanCode *clean_code,struct SourceCode *source_code);

void cleanCodeDestroy(struct CleanCode *clean_code);

void cleanCodeCleanLine(char *line);

void cleanCodeRemoveWhitespace(char *line);

void cleanCodeConvertToUpperCase(char *line);

#endif
