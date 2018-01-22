#ifndef ASSEMBLE_H
#define ASSEMBLE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sourceCode.h"

int assemble(char *source_file_name);

void parseLine(const char* line);

#endif
