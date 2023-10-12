#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int child1_running = 1;
int child2_running = 0;
pid_t child1, child2;
int timer = 0;

void switch_children(int sign) {
    if (child1_running) {
        printf("Executando o filho 1\n");
        kill(child2, SIGSTOP);
        kill(child1, SIGCONT);
        child1_running = 0;
        child2_running = 1;
    } else {
        printf("Executando o filho 2\n");
        kill(child1, SIGSTOP);
        kill(child2, SIGCONT);
        child1_running = 1;
        child2_running = 0;
    }
}

void alarmHandler(int sign) {
    alarm(1);
    timer++;
    switch_children(0);
}

int main() {
    char *ext_prog = "./ex5_eternal_loop";
    char *ext_prog_args[] = {ext_prog, NULL};

    // Filho 1
    child1 = fork();
    if (child1 < 0) {
        perror("Falha na criacao do filho 1");
        exit(1);
    } else if (child1 == 0) {
        execv(ext_prog, ext_prog_args);
        exit(1);
    }

    // Filho 2
    child2 = fork();
    if (child2 < 0) {
        perror("Falha na criacao do filho 2");
        exit(1);
    } else if (child2 == 0) {
        execv(ext_prog, ext_prog_args);
        exit(1);
    }

    // COnfigura e inicializa o alarme
    signal(SIGALRM, alarmHandler);
    alarm(1);

    while (1)
    {
        if(timer >= 15) 
        {
            kill(child1, SIGKILL);
            kill(child2, SIGKILL);
            printf("Tempo de excucao superior a 15s - filhos foram terminados.\n");
            exit(0);
        }
    }
    

    return 0;
}
