#include <stdio.h>

#include "assemble.h"

int main(int argc, char *argv[]){
    if(argc<2){
        printf("error: no input file name given\n");
    }
    else{
        assemble(argv[1]);
    }
    return 0;
}
