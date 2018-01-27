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
    malloced_code->instruction_label_value=0;

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
    next_line->instruction_label_value=0;
    return 0;
}

void sourceCodeDestroy(struct SourceCode *code){
    struct SourceCode *next_code;
    while(code!=NULL){
	next_code=code->next_line;
	free(code->line);
	free(code->clean_line);
	if(code->binary_data!=NULL){
	    free(code->binary_data);
	}
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

int sourceCodeDetermineDirective(struct SourceCode *source_code_iterator){
    char directive_name[]=".ORG";
    unsigned int i=0;
    uint32_t org_val;
    while(source_code_iterator->clean_line[i]==directive_name[i]){
	++i;
    }
    if(source_code_iterator->clean_line[i]=='#'){
	org_val=(uint32_t)strtol(&source_code_iterator->clean_line[i+1],NULL,0);
	if((org_val&0x01)!=0){
	    printf("error line %u: org value %u not alingned\n",source_code_iterator->line_number,org_val);
	    return -1;
	}
	source_code_iterator->instruction_label_value=(uint32_t)org_val;
	source_code_iterator->type=org_type;
	printf("line %u: %s is an org directive of value %u\n",source_code_iterator->line_number,
	       source_code_iterator->clean_line,
	       source_code_iterator->instruction_label_value);
	return 0;
    }
    printf("error: could not resolve directive: %s line %u",source_code_iterator->clean_line,source_code_iterator->line_number);
    return -1;
}


int sourceCodeEncodeInstruction(struct SourceCode *source_code, uint32_t position){
    char* line=(char*) source_code->clean_line;
    enum ProcessorInstructions instruction;
    unsigned char opcode;
    instruction = sourceCodeDetermineInstructionType(&line,&opcode);
    switch (instruction) {
    case ALU_instruction:
	if(sourceCodeEncodeALUInstruction(source_code,opcode,line)!=0){
	    return -1;
	}
	break;
    case INVALID_instruction:
	printf("error line %u: %s is not a valid instruction\n%s",source_code->line_number,
	       source_code->clean_line,source_code->line);
	return -1;
	break;
    default:
	break;
    }

    source_code->binary_size=1;
    return 0;
}

/* ADD ADDC ALS AND ARS
 * BR BRL
 * CMP
 * DIV
 * HALT
 * INT
 * LLS LOAD LODL LRS
 * MOV MOVN MUL
 * NOP NOR NAND
 * OR
 * PUSH POP
 * RSUB RSUBB RR RRC RL RLC
 * STOR SUB SUBB
 * TST TEQ
 * UDIV UMUL
 * XCH XOR
  */

enum ProcessorInstructions sourceCodeDetermineInstructionType(char** line_ptr,unsigned char *opcode){
    char* line=*line_ptr;
    switch (line[0]) {
    case 'A':
	switch (line[1]) {
	case 'D':
	    if(line[2]!='D')
		return INVALID_instruction;
	    if(line[3]=='C'){
		if(line[4]!='%')
		    return INVALID_instruction;
		*opcode=2;
		*line_ptr=&line[4];
		return ALU_instruction;
	    }
	    if(line[3]!='%')
		return INVALID_instruction;
	    *opcode=0;
	    *line_ptr=&line[3];
	    return ALU_instruction;
	    break;
	case 'L':
	    if(line[2]!='S')
		return INVALID_instruction;
	    if(line[3]!='%')
		return INVALID_instruction;
	    *opcode=7;
	    *line_ptr=&line[3];
	    return SHIFT_instruction;
	    break;
	case 'N':
	    break;
	case 'R':
	    break;
	default:
	    return INVALID_instruction;
	    break;
	}
	break;
    default:
	return NOP_instruction;
	break;
    }
    return NOP_instruction;
}

int sourceCodeEncodeALUInstruction(struct SourceCode *source_code_iterator,unsigned char opcode,char* parameters){
    unsigned char source_register,destination_register;
    uint32_t immediate;
    destination_register=sourceCodeDetermineRegister(&parameters);
    if(destination_register==255){
	printf("error line %u: %s doesn't have a valid destination register\n %s",source_code_iterator->line_number,
	        source_code_iterator->clean_line,source_code_iterator->line);
	return -1;
    }
    if(parameters[0]!=','){
     printf("error line %u: %s doesn't have a seperating comma\n %s",source_code_iterator->line_number,
             source_code_iterator->clean_line,source_code_iterator->line);
     return -1;
    }
    ++parameters;
    switch (parameters[0]) {
    case 0:
	printf("error line %u: %s doesn't have a second parameter\n %s",source_code_iterator->line_number,
	        source_code_iterator->clean_line,source_code_iterator->line);
	return -1;
    case '%':
	source_register=sourceCodeDetermineRegister(&parameters);
	if(source_register==255){
	    printf("error line %u: %s doesn't have a valid source register\n %s",source_code_iterator->line_number,
	            source_code_iterator->clean_line,source_code_iterator->line);
	    return -1;
	}
	source_code_iterator->binary_size=1;
	break;
    case '#':
	if(sourceCodeDetermineImmediate(&parameters,&immediate)!=0){
	    printf("error line %u: %s doesn't have a valid immediate value\n %s",source_code_iterator->line_number,
	            source_code_iterator->clean_line,source_code_iterator->line);
	    return -1;
	}
	if(immediate>>16==0){
	    source_code_iterator->binary_size=2;
	}
	else{
	    source_code_iterator->binary_size=3;
	}
	source_register=100;
	break;
    default:
	printf("error line %u: %s doesn't have a valid second parameter\n %s",source_code_iterator->line_number,
	        source_code_iterator->clean_line,source_code_iterator->line);
	return -1;
	break;
    }
    if(source_code_iterator->binary_data==NULL){
	source_code_iterator->binary_data=malloc(source_code_iterator->binary_size*sizeof(uint16_t));
    }
    else{
	source_code_iterator->binary_data=realloc(source_code_iterator->binary_data,
	                                          source_code_iterator->binary_size*sizeof(uint16_t));
    }
    if(source_code_iterator->binary_data==NULL){
	printf("error line %u: binary data malloc failed\n",source_code_iterator->line_number);
	return -1;
    }
    source_code_iterator->binary_data[0]=0;
    if(source_code_iterator->binary_size<2){
	source_code_iterator->binary_data[0]=0x4000;
	source_code_iterator->binary_data[0]|=(opcode<<8);
	source_code_iterator->binary_data[0]|=(destination_register<<4);
	source_code_iterator->binary_data[0]|=source_register;
	printf("line %u: %s = %04x\n",source_code_iterator->line_number,source_code_iterator->clean_line,
	       source_code_iterator->binary_data[0]);
    }
    else{
	source_code_iterator->binary_data[0]&=0x0200;
	source_code_iterator->binary_data[0]|=(uint16_t)(opcode<<4);
	source_code_iterator->binary_data[0]|=(uint16_t)destination_register;
	source_code_iterator->binary_data[1]=(uint16_t)immediate;
	if(source_code_iterator->binary_size<3){
	    source_code_iterator->binary_data[0]|=0x0100;
	    printf("line %u: %s = %04x:%04x\n",source_code_iterator->line_number,source_code_iterator->clean_line,
	           source_code_iterator->binary_data[0],source_code_iterator->binary_data[1]);
	}
	else{
	    source_code_iterator->binary_data[2]=(uint16_t)(immediate>>16);
	    printf("line %u: %s = %04x:%04x:%04x\n",source_code_iterator->line_number,source_code_iterator->clean_line,
	           source_code_iterator->binary_data[0],source_code_iterator->binary_data[1],
	            source_code_iterator->binary_data[2]);
	}
    }
    return 0;
}

unsigned char sourceCodeDetermineRegister(char **line_ptr){
    char* line=*line_ptr;
    while((*line)!=0&&(*line)!=','&&(*line)!='#')
	++line;
    *line_ptr=line;
    return 0;
}

int sourceCodeDetermineImmediate(char** line_ptr,uint32_t *immediate){
    *immediate=0;
    return 0;
}
