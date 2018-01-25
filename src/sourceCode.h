#ifndef SOURCE_CODE_H
#define SOURCE_CODE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

struct SourceCode
{
    char line[256];
    char clean_line[256];
    unsigned int line_number;
    struct SourceCode *next_line;
};

int sourceCodeInitialise(struct SourceCode **code,const char* line,unsigned int line_number);

int sourceCodePushBack(struct SourceCode *code,const char* line,unsigned int line_number);

const char* sourceCodeGetLine(struct SourceCode *code,unsigned int line_number);

const char* sourceCodeGetCleanLine(struct SourceCode *code,unsigned int line_number);

void sourceCodeDestroy(struct SourceCode **code);

void sourceCodePrint(struct SourceCode *code);

void sourceCodeCleanLine(const char *line);

void sourceCodeRemoveWhitespace(const char *line);

void sourceCodeConvertToUpperCase(const char *line);

#endif
