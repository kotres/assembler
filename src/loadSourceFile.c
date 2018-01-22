#include "loadSourceFile.h"
#define FILE_BUFFER_SIZE 256

int loadSourceFile(char *source_file_name, char **source_code){
    FILE *source_file_pointer;
    unsigned int file_size;

    source_file_pointer = fopen(source_file_name,"r");
    if(source_file_pointer==NULL){
	printf("error: failed to open file %s\n",source_file_name);
	return -1;
    }

    file_size=getSourceFileSize(source_file_pointer);
    if(file_size==0){
	printf("error: empty file detected");
	fclose(source_file_pointer);
	return -1;
    }

    source_code=malloc(file_size * sizeof(char*));
    if(source_code==NULL){
	printf("error: source code malloc failed");
	fclose(source_file_pointer);
	return -1;
    }

    if(ferror(source_file_pointer)){
	printf("I/O error when reading");
	fclose(source_file_pointer);
	return -1;
    }
    fclose(source_file_pointer);
    return 0;
}

unsigned int getSourceFileSize(FILE *fp){
    char fileBuffer[FILE_BUFFER_SIZE];
    unsigned int i=0;
    while(fgets(fileBuffer,FILE_BUFFER_SIZE,(FILE*)fp)){
	if(!isLineEmpty(fileBuffer)){
	    ++i;
	}
    }
    rewind(fp);
    return i;
}

int isLineEmpty(char *line){
    char *line_temp=line;
    while(line_temp[0]==' '||line_temp[0]=='\t'){
	++line_temp;
    }
    if(line_temp[0]==0)
	return 1;
    if(line_temp[0]==';')
	return 1;
    if(line_temp[0]=='\n')
	return 1;
    if(line_temp[0]=='\r')
	return 1;
    return 0;
}
