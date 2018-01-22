#include "assemble.h"

int assemble(char *source_file_name){
    char **source_code=NULL;
    int return_val;
    return_val = loadSourceFile(source_file_name,source_code);
    free(source_code);
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
