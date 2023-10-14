//Lucas Toscano Pimentel Appolinário Cerqueira
//2110695


#include  <stdio.h>
#include  <stdlib.h>

int main(int argc, char *argv[]){
    FILE *fp;
    char line[256];

    if ((fp=fopen (argv[1],"r"))==NULL){
        printf ("Erro na abertura do arquivo.");
    }
    else{
        while (fgets(line, sizeof(line), fp) != NULL) {
            printf("%s", line);
        }
    }
    fclose(fp);

    printf("\n");
    return 0;
}
