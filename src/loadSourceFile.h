#ifndef LOAD_SOURCE_FILE_H
#define LOAD_SOURCE_FILE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int loadSourceFile(char* source_file_name, char** source_code);

unsigned int getSourceFileSize(FILE *fp);

void cleanLine(char* line);

void removeWhitespace(char* line);

int isLineEmpty(char* line);

#endif
