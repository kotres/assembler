#include "assembler.h"

int assemblerInitialise(struct Assembler *assembler, char *source_file_name){
    assembler->location_counter=0;
    if(sourceCodeInitialise(&assembler->source_code,source_file_name)!=0){
	return -1;
    }
    if(cleanCodeInitialize(&assembler->clean_code,&assembler->source_code)!=0){
	return -1;
    }
    return 0;
}

int assemblerAssemble(struct Assembler *assembler){
   /* unsigned int i=0;
    char cleaned_line[256];
    for(i=0;i<assembler->source_code.line_size;++i){
	strcpy(cleaned_line,sourceCodeGetLine(&assembler->source_code,i));
	assemblerCleanLine(cleaned_line);
	if(assemblerParseLine(assembler,cleaned_line)==-1){
	    printf("error parsing line %u: %s",(i+1),sourceCodeGetLine(&assembler->source_code,i));
	    return -1;
	}
	assembler->location_counter++;
    }*/

    return 0;
}

/*void assemblerCleanLine(char *line){
    char *end_of_line;
    assemblerRemoveWhitespace(line);
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
    assemblerConvertToUpperCase(line);
}

void assemblerRemoveWhitespace(char *line){
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

void assemblerConvertToUpperCase(char *line){
    char* lower_case_character=line;
    while(*lower_case_character!=0){
	*lower_case_character=(char)(toupper(*lower_case_character));
	lower_case_character++;
    }
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
    sourceCodeDestroy(&assembler->source_code);
    cleanCodeDestroy(&assembler->clean_code);
}
