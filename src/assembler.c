#include "assembler.h"

void assemblerInitialise(struct Assembler *assembler){
    assembler->location_counter=0;
    assembler->labels=NULL;
    assembler->source_code=NULL;
}

int assemblerAssemble(struct Assembler *assembler,const char *source_file_name){
    FILE *source_file_pointer;

    char file_buffer[MAXIMUM_LINE_LENGTH];
    unsigned int i=0;

    source_file_pointer = fopen(source_file_name,"r");
    if(source_file_pointer==NULL){
	printf("error: failed to open file %s\n",source_file_name);
	return -1;
    }

    while(fgets(file_buffer,MAXIMUM_LINE_LENGTH,(FILE*)source_file_pointer)){
	if(assembler->source_code==NULL){
	    if(sourceCodeInitialise(&assembler->source_code,file_buffer,i)!=0)
	    {
		printf("error: failed to initialize source code list\n");
		return -1;
	    }
	}
	else{
	    if(sourceCodePushBack(assembler->source_code,file_buffer,i)!=0)
	    {
		printf("error: failed to push back source code list\n");
		return -1;
	    }
	}
	++i;
    }

    if(ferror(source_file_pointer)){
	printf("I/O error when reading");
	fclose(source_file_pointer);
	return -1;
    }
    printf("%s loaded to memory\n",source_file_name);
    fclose(source_file_pointer);

    sourceCodePrint(assembler->source_code);

    return 0;
}

/*int assemblerFindLabels(struct Assembler *assembler){
    unsigned int i=0;
    char line[256],*name_ptr;
    for(i=0;i<assembler->clean_code.size;++i){
	name_ptr=cleanCodeGetLine(&assembler->clean_code,i);
	if(name_ptr==NULL){
	    printf("error retrieving line %u for label finding",i);
	    return -1;
	}
	if(*name_ptr=='@'){
	    name_ptr++;
	    strcpy(line,name_ptr);
	    if(strlen(line)<2){
		printf("error: bad label at line %u: %s",i,line);
		return -1;
	    }
	    while(*name_ptr!=0)
		name_ptr++;
	    name_ptr--;
	    if(*name_ptr==':'){
		name_ptr=line;
		while(*name_ptr!=':')
		    name_ptr++;
		*name_ptr=0;
		/*printf("found label %s\n",line);*/
                /*if(assembler->labels==NULL){
		    labelInitialize(assembler->labels,0,0,line);
		}
		else{
		    labelPushBack(assembler->labels,0,0,line);
		}
	    }
	    else{
		printf("error: bad label at line %u: %s",i,line);
		return -1;
	    }
	}
    }
    return 0;
}*/

/* ADD ADDC ALS AND ARS
 * BR BRL
 * CMP
 * DIV
 * HALT
 * INT
 * LLS LOAD LOADS LODL LODLS LRS
 * MOV MOVN MUL
 * NOP NOR NAND
 * OR
 * PUSH PUSHS POP POPS
 * RSUB RSUBB RR RRC RL RLC
 * STOR STORS SUB SUBB
 * TST TEQ
 * UDIV UMUL
 * XCH XOR
  */
/*int assemblerParseLine(struct Assembler *assembler, char *line){
    switch (line[0]) {
    case 0:
	return 0;
	break;
    case '.':
	printf("%s assembler instruction\n",line);
	break;
    case '@':
	printf("%s label\n",line);
	break;
    default:
	printf("%s\n",line);
	break;
    }
    return 0;
}


int assemblerDetectInstruction(char *line){
    switch (line[0]) {
    case 0:
	break;
    case 'A':
	switch (line[1]) {
	case 0:
	    return -1;
	    break;
	case 'D':
	    printf("AD\n");
	    break;
	case 'L':
	    printf("AL\n");
	    break;
	case 'N':
	    printf("AN\n");
	    break;
	case 'R':
	    printf("AR\n");
	    break;
	default:
	    break;
	}
	break;
    case 'B':
	printf("B\n");
	break;
    case 'C':
	printf("C\n");
	break;
    case 'D':
	printf("D\n");
	break;
    case 'H':
	printf("H\n");
	break;
    case 'I':
	printf("I\n");
	break;
    case 'L':
	printf("L\n");
	break;
    case 'M':
	printf("M\n");
	break;
    case 'N':
	printf("N\n");
	break;
    case 'O':
	printf("O\n");
	break;
    case 'P':
	printf("P\n");
	break;
    case 'R':
	printf("R\n");
	break;
    case 'S':
	printf("S\n");
	break;
    case 'T':
	printf("T\n");
	break;
    case 'U':
	printf("U\n");
	break;
    case 'X':
	printf("X\n");
	break;
    default:
	return -1;
	break;
    }
    return 1;

}*/

void assemblerDestroy(struct Assembler *assembler){
    printf("assembler destroyed");
}
