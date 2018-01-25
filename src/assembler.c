#include "assembler.h"

void assemblerInitialise(struct Assembler *assembler){
    assembler->location_counter=0;
    assembler->labels=NULL;
    assembler->source_code=NULL;
}

int assemblerAssemble(struct Assembler *assembler,const char *source_file_name){

    if(assemblerLoadSourceCode(assembler,source_file_name)!=0){
	return -1;
    }

    if(assemblerFindLabels(assembler)!=0){
	return -1;
    }

    if(assemblerDecodeSourceCode(assembler)!=0){
	return -1;
    }

    return 0;
}

int assemblerLoadSourceCode(struct Assembler *assembler,const char *source_file_name){
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

    if(assembler->source_code==NULL){
	printf("error: source code contained no instructions\n");
	return -1;
    }

    printf("%s loaded to memory:\n",source_file_name);
    fclose(source_file_pointer);

    /*sourceCodePrint(assembler->source_code);*/

    return 0;
}

int assemblerFindLabels(struct Assembler *assembler){
    struct SourceCode *source_code_iterator=assembler->source_code;
    char label_name[256];
    unsigned int line_character;
    while(source_code_iterator!=NULL){
	if(source_code_iterator->clean_line[0]=='@'){
	    if(source_code_iterator->clean_line[1]==0||source_code_iterator->clean_line[0]==':'){
		printf("label error: line %u has an empty label: %s",
		       source_code_iterator->line_number,source_code_iterator->line);
		return -1;
	    }
	    line_character=1;
	    while(source_code_iterator->clean_line[line_character]!=':'&&source_code_iterator->clean_line[line_character]!=0){
		label_name[line_character-1]=source_code_iterator->clean_line[line_character];
		line_character++;
	    }
	    if(source_code_iterator->clean_line[line_character]==':'){
		label_name[line_character-1]=0;
		if(assembler->labels==NULL){
		    if(labelInitialize(&assembler->labels,0,label_name)!=0)
			return -1;
		}
		else{
		    if(labelPushBack(assembler->labels,0,label_name)!=0)
			return -1;
		}
		source_code_iterator->label=labelEnd(assembler->labels);
		source_code_iterator->binary_size=0;
		source_code_iterator->type=label_type;
	    }
	}
	source_code_iterator=source_code_iterator->next_line;
    }

    /*labelPrintLabels(assembler->labels);*/

    return 0;
}

int assemblerDecodeSourceCode(struct Assembler *assembler){
    struct SourceCode *source_code=assembler->source_code;
    while(source_code!=NULL){
	assemblerParseLine(assembler,&source_code);
	source_code=source_code->next_line;
    }
    return 0;
}

int assemblerParseLine(struct Assembler *assembler,struct SourceCode **iterator_pointer){
    struct SourceCode *iterator=*iterator_pointer;
    switch (iterator->clean_line[0]) {
    case '.':
	iterator->binary_size=0;
	iterator->type=assembler_directive_type;
	printf("%u: %s is an assembler directive\n",iterator->line_number,iterator->clean_line);
	break;
    case'@':
	printf("%u: %s is label %s: %u\n",iterator->line_number,iterator->clean_line,
	       iterator->label->name,iterator->label->address);
	if(iterator->label->address!=assembler->location_counter){
	    iterator->label->address=assembler->location_counter;
	    *iterator_pointer=assembler->source_code;
	    assembler->location_counter=0;
	}
	break;
    default:
	assembler->location_counter++;
	break;
    }
    return 0;
}

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
    sourceCodeDestroy(assembler->source_code);
    labelDestroy(assembler->labels);
    printf("assembler destroyed\n");
}
