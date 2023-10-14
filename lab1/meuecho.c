//Lucas Toscano Pimentel Appolinário Cerqueira
//2110695


#include  <stdio.h>
#include  <stdlib.h>

int main(int argc, char *argv[]){

    for(int i = 1; i < argc; i++){
        printf("%s ", argv[i]);
    }

    printf("\n");

    return 0;
}
