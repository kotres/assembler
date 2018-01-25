#ifndef SOURCE_CODE_H
#define SOURCE_CODE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

#include "label.h"

enum SourceCodeType{
    label_type,
    label_dependent_code_type,
    static_code_type,
    assembler_directive_type,
    not_determined_type
};

struct SourceCode
{
    char *line;
    char *clean_line;
    unsigned int line_number;
    struct SourceCode *next_line;

    unsigned int binary_size;
    uint32_t *binary_data;
    enum SourceCodeType type;
    struct Label *label;

};

int sourceCodeInitialise(struct SourceCode **code,const char* line,unsigned int line_number);

int sourceCodePushBack(struct SourceCode *code,const char* line,unsigned int line_number);

const char* sourceCodeGetCleanLine(struct SourceCode *code,unsigned int line_number);

void sourceCodeDestroy(struct SourceCode *code);

void sourceCodePrint(struct SourceCode *code);

void sourceCodeCleanLine(const char *line);

void sourceCodeRemoveWhitespace(const char *line);

void sourceCodeConvertToUpperCase(const char *line);

#endif
