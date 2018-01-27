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

    if(assemblerDetermineLines(assembler)!=0){
	return -1;
    }

    if(assemblerResolveLabelValues(assembler)!=0){
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

    printf("finding labels\n");

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
		printf("found label %s at line %u\n",label_name,source_code_iterator->line_number);
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

int assemblerDetermineLines(struct Assembler *assembler){
    struct SourceCode *source_code_iterator=assembler->source_code;
    char label_name[256];
    unsigned int i=0,j=0;
    printf("determining non label source code lines\n");
    while(source_code_iterator!=NULL){
	switch (source_code_iterator->clean_line[0]) {
	case '.':
	    if(sourceCodeDetermineDirective(source_code_iterator)!=0){
		return -1;
	    }
	    assembler->location_counter=source_code_iterator->instruction_label_value;
	    break;
	case '@':
	    source_code_iterator->label->address=assembler->location_counter;
	    break;
	default:
	    i=0;
	    j=0;
	    while(source_code_iterator->clean_line[i]!=0&&source_code_iterator->clean_line[i]!='@'){
		++i;
	    }
	    if(source_code_iterator->clean_line[i]=='@'){
		++i;
		while(source_code_iterator->clean_line[i]!=0&&source_code_iterator->clean_line[i]!=','){
		    label_name[j]=source_code_iterator->clean_line[i];
		    i++;
		    j++;
		}
		label_name[j]=0;
		printf("line %u: %s is a label dependent instruction with label %s\n",source_code_iterator->line_number,
		       source_code_iterator->clean_line,
		       label_name);
		source_code_iterator->label=labelFindLabel(assembler->labels,label_name);
		if(source_code_iterator->label==NULL){
		    printf("error: could not find label %s\n",label_name);
		    return -1;
		}
		source_code_iterator->type=label_dependent_code_type;
		source_code_iterator->instruction_label_value=source_code_iterator->label->address;
	    }
	    else{
		source_code_iterator->label=NULL;
		source_code_iterator->type=static_code_type;
		printf("line %u: %s is either a static instruction or a position dependent one\n",
		       source_code_iterator->line_number,
		       source_code_iterator->clean_line);
	    }
	    if(sourceCodeEncodeInstruction(source_code_iterator,assembler->location_counter)!=0){
		return -1;
	    }
	    assembler->location_counter+=source_code_iterator->binary_size;
	    break;
	}
	source_code_iterator=source_code_iterator->next_line;
    }
    return 0;
}

int assemblerResolveLabelValues(struct Assembler *assembler){
    struct SourceCode *source_code=assembler->source_code;
    unsigned int code_size;
    assembler->location_counter=0;
    printf("resolving label values\n");
    while(source_code!=NULL){
	switch (source_code->type) {
	case label_dependent_code_type:
	    code_size=source_code->binary_size;
	    if(source_code->instruction_label_value!=source_code->label->address){
		printf("rewriting %u line due to outdated label value\n",source_code->line_number);
		source_code->instruction_label_value=source_code->label->address;
	    }
	    if(source_code->binary_size==code_size){
		assembler->location_counter+=source_code->binary_size;
		source_code=source_code->next_line;
	    }
	    else{
		assembler->location_counter=0;
		source_code=assembler->source_code;
	    }
	    break;
	case position_dependent_code_type:
	    code_size=source_code->binary_size;
	    printf("rewriting %u line due to possible outdated position value\n",source_code->line_number);
	    if(source_code->binary_size==code_size){
		assembler->location_counter+=source_code->binary_size;
		source_code=source_code->next_line;
	    }
	    else{
		assembler->location_counter=0;
		source_code=assembler->source_code;
	    }
	    break;
	case org_type:
	    assembler->location_counter=source_code->instruction_label_value;
	    source_code=source_code->next_line;
	    break;
	case label_type:
	    if(source_code->label->address!=assembler->location_counter){
		printf("changing label %s value from %u to %u\n",source_code->label->name,source_code->label->address,
		       assembler->location_counter);
		source_code->label->address=assembler->location_counter;
		assembler->location_counter=0;
		source_code=assembler->source_code;
	    }
	    else{
		source_code=source_code->next_line;
	    }
	    break;
	default:
	    assembler->location_counter+=source_code->binary_size;
	    source_code=source_code->next_line;
	    break;
	}
    }
    return 0;
}



void assemblerDestroy(struct Assembler *assembler){
    sourceCodeDestroy(assembler->source_code);
    labelDestroy(assembler->labels);
    printf("assembler destroyed\n");
}
