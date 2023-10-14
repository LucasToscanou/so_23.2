//Lucas Toscano Pimentel Appolinário Cerqueira
//2110695


#include  <stdio.h>
#include  <stdlib.h>
#include  <unistd.h>
#include  <sys/wait.h>


int main(){
    int n = 3;
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Erro ao criar um processo filho\n");
        return 1;
    } 
    else if (pid == 0) {
        // Filho
        for (int i = 0; i < 10000; i++) {
            n += 10;
        }
        printf("processo filho, pid=%d, n=%d\n", getpid(), n);
    } 
    else {
        // Pai
        for (int i = 0; i < 10000; i++) {
            n += 1;
        }
        printf("processo pai, pid=%d, n=%d\n", getpid(), n);
        
        int status = 0;
        waitpid(-1, &status, 0);
    }


    return 0;
}

/*
Os valores de pid são diferentes porque o pai e o filho são processos diferentes.
Os valores de n são diferentes porque, no momento do fork, é criada uma memória virtual 
que armazena o valor de n = 3. Com isso, os processos pai e filho podem acessar o valor de
n original sem que as operações de um afetem o outro.
*/