#include "sourceCode.h"

int sourceCodeInitialise(struct SourceCode **code,const char* line,unsigned int line_number){
    char line_buffer[256];
    struct SourceCode *malloced_code;
    if(*code!=NULL){
	printf("source code initialisation error: non NULL pointer given\n");
	return -1;
    }
    strncpy(line_buffer,line,sizeof(line_buffer));
    if(line_buffer[0]==0)
	return 0;
    sourceCodeCleanLine(line_buffer);
    if(line_buffer[0]==0)
	return 0;
    *code=(struct SourceCode*)malloc(sizeof(struct SourceCode));
    if(*code==NULL){
	printf("source code initialisation error: malloc failed\n");
	return -1;
    }
    malloced_code=*code;

    malloced_code->line=(char *)malloc((strlen(line)+1)*sizeof(char));
    if(malloced_code->line==NULL){
	printf("source code initialisation error: line malloc failed\n");
	return -1;
    }

    malloced_code->clean_line=(char *)malloc((strlen(line_buffer)+1)*sizeof(char));
    if(malloced_code->clean_line==NULL){
	printf("source code initialisation error: clean line malloc failed\n");
	return -1;
    }

    strcpy(malloced_code->line,line);
    strcpy(malloced_code->clean_line,line_buffer);
    malloced_code->line_number=line_number;
    malloced_code->next_line=NULL;
    malloced_code->binary_data=NULL;
    malloced_code->binary_size=0;
    malloced_code->label=NULL;
    malloced_code->type=not_determined_type;

    return 0;
}

int sourceCodePushBack(struct SourceCode *code,const char* line,unsigned int line_number){
    char line_buffer[256];
    struct SourceCode *next_line;
    if(code==NULL){
	printf("source code push back error: NULL pointer given\n");
	return -1;
    }

    while(code->next_line!=NULL){
	code=code->next_line;
    }

    strncpy(line_buffer,line,sizeof(line_buffer));
    if(line_buffer[0]==0)
	return 0;
    sourceCodeCleanLine(line_buffer);
    if(line_buffer[0]==0)
	return 0;
    code->next_line=(struct SourceCode*)malloc(sizeof(struct SourceCode));
    if(code->next_line==NULL){
	printf("source code push back error: malloc failed\n");
	return -1;
    }

    next_line=code->next_line;

    next_line->line=(char *)malloc((strlen(line)+1)*sizeof(char));
    if(next_line->line==NULL){
	printf("source code initialisation error: line malloc failed\n");
	return -1;
    }

    next_line->clean_line=(char *)malloc((strlen(line_buffer)+1)*sizeof(char));
    if(next_line->clean_line==NULL){
	printf("source code initialisation error: clean line malloc failed\n");
	return -1;
    }

    strcpy(next_line->line,line);
    strcpy(next_line->clean_line,line_buffer);
    next_line->line_number=line_number;
    next_line->next_line=NULL;
    next_line->binary_data=NULL;
    next_line->binary_size=0;
    next_line->label=NULL;
    next_line->type=not_determined_type;
    return 0;
}

void sourceCodeDestroy(struct SourceCode *code){
    struct SourceCode *next_code;
    while(code!=NULL){
	next_code=code->next_line;
	free(code->line);
	free(code->clean_line);
	free(code);
	code=next_code;
    }
    printf("source code freed from memory\n");
}

void sourceCodePrint(struct SourceCode *code){
    while(code!=NULL){
	printf("%u: %s %s\n",code->line_number,code->line,code->clean_line);
	code=code->next_line;
    }
}

void sourceCodeCleanLine(const char *line){
    char *end_of_line=NULL;
    sourceCodeRemoveWhitespace(line);
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
    sourceCodeConvertToUpperCase(line);
}


void sourceCodeRemoveWhitespace(const char *line){
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

void sourceCodeConvertToUpperCase(const char *line){
    char* lower_case_character=(char*)line;
    while(*lower_case_character!=0){
	*lower_case_character=(char)(toupper(*lower_case_character));
	lower_case_character++;
    }
}
