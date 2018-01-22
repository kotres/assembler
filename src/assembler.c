#include "assembler.h"

int assemblerInitialise(struct Assembler *assembler, char *source_file_name, char *binary_file_name){
    assembler->location_counter=0;
    return sourceCodeInitialise(&assembler->source_code,source_file_name);
}

int assemblerAssemble(struct Assembler *assembler){
    return 0;
}

void assemblerParseLine(const char *line){
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

void assemblerDestroy(struct Assembler *assembler){
    sourceCodeDestroy(&assembler->source_code);
    assembledCodeDestroy(&assembler->assembled_code);
}
