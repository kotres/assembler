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

    code->line_size=sourceCodeGetFileLineSize(source_file_pointer);
    if(code->line_size==0){
	printf("error: empty file detected");
	fclose(source_file_pointer);
	return -1;
    }

    code->data=malloc( code->line_size * sizeof(char*));
    if(code->data==NULL){
	printf("error: source code malloc failed");
	fclose(source_file_pointer);
	return -1;
    }

    while(fgets(fileBuffer,FILE_BUFFER_SIZE,(FILE*)source_file_pointer)){
	code->data[i]=malloc((strlen(fileBuffer)+1)*sizeof(char));
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

/*int load_lines(FILE *fp, unsigned int file_size, char **source_code){
    char fileBuffer[FILE_BUFFER_SIZE];
    unsigned int i=0;
    while(fgets(fileBuffer,FILE_BUFFER_SIZE,(FILE*)fp)){
	if(!isLineEmpty(fileBuffer)){
	    cleanLine(fileBuffer);
	    printf("%s %lu\n",fileBuffer,strlen(fileBuffer));
	    source_code[i]=malloc((strlen(fileBuffer)+1)*sizeof(char));
	    ++i;
	}
    }
}*/

unsigned int sourceCodeGetFileLineSize(FILE *fp){
    char fileBuffer[FILE_BUFFER_SIZE];
    unsigned int i=0;
    while(fgets(fileBuffer,FILE_BUFFER_SIZE,(FILE*)fp)){
	++i;
    }
    rewind(fp);
    return i;
}

void sourceCodeDestroy(struct SourceCode *code){
    unsigned int i=0;
    for(i=0;i<code->line_size;++i){
	free(code->data[i]);
    }
    free(*code->data);
}

/*int isLineEmpty(char *line){
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

void removeWhitespace(char *line){
    char *whitespace_position;
    char *p;
    whitespace_position=strchr(line, ' ');
    while(whitespace_position!=NULL){
	p=whitespace_position;
	while(*p!=0){
	    *p=*(p+1);
	    p++;
	}
	whitespace_position=strchr(line, ' ');
    }
    whitespace_position=strchr(line, '\t');
    while(whitespace_position!=NULL){
	p=whitespace_position;
	while(*p!=0){
	    *p=*(p+1);
	    p++;
	}
	whitespace_position=strchr(line, '\t');
    }
}

void cleanLine(char *line){
    char *end_of_line;
    removeWhitespace(line);
    end_of_line=strchr(line, ';');
    if(end_of_line!=NULL){
	*end_of_line=0;
    }
    end_of_line=strchr(line, '\r');
    if(end_of_line!=NULL){
	*end_of_line=0;
    }
    end_of_line=strchr(line, '\n');
    if(end_of_line!=NULL){
	*end_of_line=0;
    }
}*/
