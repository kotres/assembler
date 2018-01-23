#ifndef INTERMEDIATE_CODE_H
#define INTERMEDIATE_CODE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct IntermediateCode
{
    unsigned int source_code_line;
    unsigned int size;
    uint16_t *data;
};

#endif
