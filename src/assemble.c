#include "assemble.h"

int assemble(char *source_file_name){
    struct SourceCode source_code;
    int return_val;
    return_val = sourceCodeInitialise(&source_code,source_file_name);
    sourceCodeDestroy(&source_code);
    return return_val;
}

void parseLine(const char *line){
    printf("%s",line);
    switch (line[0]) {
    case 'A':
        printf("0x0\n");
        break;
    default:
        printf("not parsed yet\n");
        break;
    }
}
