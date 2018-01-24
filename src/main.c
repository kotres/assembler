#include <stdio.h>
#include <stdlib.h>

#include "assembler.h"

int main(int argc, char *argv[]){
    struct Assembler assembler;
    if(argc<2){
        printf("error: no input file name given\n");
        return EXIT_FAILURE;
    }
    if(assemblerInitialise(&assembler,argv[1])!=0){
	return EXIT_FAILURE;
    }
    if(!assemblerAssemble(&assembler)){
	assemblerDestroy(&assembler);
	return EXIT_FAILURE;
    }

    assemblerDestroy(&assembler);

    return EXIT_SUCCESS;
}
