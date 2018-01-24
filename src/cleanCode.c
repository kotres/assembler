#include "cleanCode.h"

int cleanCodeInitialize(struct CleanCode *clean_code,struct SourceCode *source_code){
    unsigned int i=0;
    char clean_line[256];
    char* source_code_line;
    clean_code->size=source_code->size;
    if(clean_code->size==0){
	printf("error: empty source code file given to code cleaner");
	return -1;
    }
    clean_code->data=(char**)malloc(clean_code->size*sizeof(char*));
    if(clean_code->data==NULL){
	printf("error: clean code malloc failed");
	return -1;
    }

    for(i=0;i<clean_code->size;++i){
	source_code_line=sourceCodeGetLine(source_code,i);
	if(source_code_line==NULL){
	    printf("error: couldn't retrive line %u from source code for cleaning",i);
	    return -1;
	}
	strcpy(clean_line,source_code_line);
	cleanCodeCleanLine(clean_line);
	clean_code->data[i]=(char*)malloc((strlen(clean_line)+1)*sizeof(char));
	if(clean_code->data[i]==NULL){
	    printf("error: clean code line malloc failed");
	    return -1;
	}
	strcpy(clean_code->data[i],clean_line);
	printf("%s\n",clean_code->data[i]);
    }

    return 0;
}


void cleanCodeCleanLine(char *line){
    char *end_of_line=NULL;
    cleanCodeRemoveWhitespace(line);
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
    cleanCodeConvertToUpperCase(line);
}


void cleanCodeRemoveWhitespace(char *line){
    char *whitespace_position=NULL;
    char *p=NULL;
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

void cleanCodeConvertToUpperCase(char *line){
    char* lower_case_character=line;
    while(*lower_case_character!=0){
	*lower_case_character=(char)(toupper(*lower_case_character));
	lower_case_character++;
    }
}

void cleanCodeDestroy(struct CleanCode *code){
    unsigned int i=0;
    for(i=0;i<code->size;++i){
	free(code->data[i]);
    }
    free(*code->data);
}
