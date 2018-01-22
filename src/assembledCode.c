#include "assembledCode.h"

int assembledCodeInitialize(struct AssembledCode *code, unsigned int size, char *name){
    code->name=name;
    code->line_size=size;
    code->data=malloc(size*sizeof(uint16_t));
    if(code->data==NULL){
	return -1;
    }
    return 0;
}

void assembledCodeDestroy(struct AssembledCode *code){
    free(code->data);
}
