#ifndef ASSEMBLED_CODE
#define ASSEMBLED_CODE

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct AssembledCode
{
    uint16_t* data;
    char* name;
    unsigned int line_size;

};

int assembledCodeInitialize(struct AssembledCode *code,unsigned int size,char* name);

void assembledCodeDestroy(struct AssembledCode *code);

#endif
