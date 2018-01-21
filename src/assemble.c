#include "assemble.h"

int assemble(const char *source_file_name){
    FILE *source_file_pointer;
    char source_file_buffer[255];

    printf("assembling %s\n",source_file_name);

    source_file_pointer = fopen(source_file_name,"r");

    if(source_file_pointer==NULL){
        printf("error: failed to open file %s\n",source_file_name);
        return -1;
    }
    while(fgets(source_file_buffer,255,(FILE*)source_file_pointer)){
        parseLine(source_file_buffer);
    }
    if(ferror(source_file_pointer)){
        printf("I/O error when reading");
        fclose(source_file_pointer);
        return -1;
    }
    fclose(source_file_pointer);
    return 0;
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
