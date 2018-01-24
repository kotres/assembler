#ifndef SOURCE_CODE_H
#define SOURCE_CODE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct SourceCode
{
    char* name;
    char** data;
    unsigned int size;
};

int sourceCodeInitialise(struct SourceCode *code,char* source_file_name);

unsigned int sourceCodeGetFileLineSize(FILE *fp);

char* sourceCodeGetLine(struct SourceCode *code,unsigned int line_number);

void sourceCodeDestroy(struct SourceCode *code);


#endif
