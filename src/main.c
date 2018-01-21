#include <stdio.h>
#include <stdlib.h>

#include "assemble.h"

int main(int argc, char *argv[]){
    if(argc<2){
        printf("error: no input file name given\n");
        return EXIT_FAILURE;
    }
    if(!assemble(argv[1])){
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
