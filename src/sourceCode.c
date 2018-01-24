#include "sourceCode.h"
#define FILE_BUFFER_SIZE 256

int sourceCodeInitialise(struct SourceCode *code,char* source_file_name){
    FILE *source_file_pointer;

    char fileBuffer[FILE_BUFFER_SIZE];
    unsigned int i=0;

    source_file_pointer = fopen(source_file_name,"r");
    if(source_file_pointer==NULL){
	printf("error: failed to open file %s\n",source_file_name);
	return -1;
    }

    code->size=sourceCodeGetFileLineSize(source_file_pointer);
    if(code->size==0){
	printf("error: empty file detected");
	fclose(source_file_pointer);
	return -1;
    }

    code->data=(char**)malloc( code->size * sizeof(char*));
    if(code->data==NULL){
	printf("error: source code malloc failed");
	fclose(source_file_pointer);
	return -1;
    }

    while(fgets(fileBuffer,FILE_BUFFER_SIZE,(FILE*)source_file_pointer)){
	code->data[i]=(char*)malloc((strlen(fileBuffer)+1)*sizeof(char));
	if(code->data[i]==NULL){
	    printf("error: source code line malloc failed");
	    fclose(source_file_pointer);
	    return -1;
	}
	strcpy(code->data[i], fileBuffer);
	++i;
    }

    if(ferror(source_file_pointer)){
	printf("I/O error when reading");
	fclose(source_file_pointer);
	return -1;
    }
    printf("%s loaded to memory\n",source_file_name);
    fclose(source_file_pointer);

    code->name=source_file_name;
    return 0;
}

unsigned int sourceCodeGetFileLineSize(FILE *fp){
    char fileBuffer[FILE_BUFFER_SIZE];
    unsigned int i=0;
    while(fgets(fileBuffer,FILE_BUFFER_SIZE,(FILE*)fp)){
	++i;
    }
    rewind(fp);
    return i;
}

char* sourceCodeGetLine(struct SourceCode *code,unsigned int line_number){
    if(line_number>code->size){
	return NULL;
    }
    return code->data[line_number];
}

void sourceCodeDestroy(struct SourceCode *code){
    unsigned int i=0;
    for(i=0;i<code->size;++i){
	free(code->data[i]);
    }
    free(*code->data);
}

